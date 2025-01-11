// kmeans.c
#include "kmeans.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define threshold 0.001

double euclidean_distance(double *v1, double *v2, int length) {
    int i = 0;
    double dist = 0;

    for (i = 0; i < length; i++) {
        dist += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }

    return dist;
}

void kmeans_process(data_struct *data_in, data_struct *clusters, double *newCentroids, double *SumOfDist, double *sse) {
    int i, j, k;
    double tmp_dist = 0;
    int tmp_index = 0;
    double min_dist = 0;
    double *dataset = data_in->dataset;
    double *centroids = clusters->dataset;
    unsigned int *Index = data_in->members;
    unsigned int *cluster_size = clusters->members;

    for (i = 0; i < clusters->secondary_dim; i++) {
        cluster_size[i] = 0;
    }

    for (i = 0; i < data_in->secondary_dim; i++) {
        tmp_dist = 0;
        tmp_index = 0;
        min_dist = FLT_MAX;

        for (k = 0; k < clusters->secondary_dim; k++) {
            tmp_dist = euclidean_distance(dataset + i * data_in->leading_dim, centroids + k * clusters->leading_dim, data_in->leading_dim);
            if (tmp_dist < min_dist) {
                min_dist = tmp_dist;
                tmp_index = k;
            }
        }

        Index[i] = tmp_index;
        SumOfDist[0] += min_dist;
        sse[0] += min_dist * min_dist;
        cluster_size[tmp_index]++;

        for (j = 0; j < data_in->leading_dim; j++) {
            newCentroids[tmp_index * clusters->leading_dim + j] += dataset[i * data_in->leading_dim + j];
        }
    }

    for (k = 0; k < clusters->secondary_dim; k++) {
        for (j = 0; j < data_in->leading_dim; j++) {
            centroids[k * clusters->leading_dim + j] = newCentroids[k * clusters->leading_dim + j];
        }
    }
}

void cluster(data_struct *data_in, data_struct *clusters, int max_iterations) {
    int iter, i, j, k, dest;
    double SumOfDist = 0, new_SumOfDist = 0, part_SumOfDist, sse = 0, psse;
    double *newCentroids, *partCentroids;
    unsigned int *part_size;
    int endcond = 0;

    int rank, NumTasks;
    MPI_Comm_size(MPI_COMM_WORLD, &NumTasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat;

    part_size = (unsigned int *)malloc(clusters->secondary_dim * sizeof(unsigned int));
    newCentroids = (double *)malloc(clusters->leading_dim * clusters->secondary_dim * sizeof(double));
    partCentroids = (double *)malloc(clusters->leading_dim * clusters->secondary_dim * sizeof(double));

    for (iter = 0; iter < max_iterations; iter++) {
        if (rank == 0) {
            new_SumOfDist = 0;

            for (k = 0; k < clusters->secondary_dim; k++) {
                part_size[k] = (unsigned int)0;
                clusters->members[k] = 0;
            }

            MPI_Bcast(clusters->dataset, clusters->leading_dim * clusters->secondary_dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            for (i = 0; i < clusters->secondary_dim; i++) {
                for (j = 0; j < clusters->leading_dim; j++) {
                    newCentroids[i * clusters->leading_dim + j] = 0;
                }
            }

            MPI_Reduce(&part_SumOfDist, &new_SumOfDist, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(partCentroids, newCentroids, clusters->leading_dim * clusters->secondary_dim, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            for (dest = 1; dest < NumTasks; dest++) {
                MPI_Recv(part_size, clusters->secondary_dim, MPI_UNSIGNED, dest, 5, MPI_COMM_WORLD, &stat);

                for (k = 0; k < clusters->secondary_dim; k++) {
                    clusters->members[k] += part_size[k];
                }
            }

            for (k = 0; k < clusters->secondary_dim; k++) {
                for (j = 0; j < clusters->leading_dim; j++) {
                    clusters->dataset[k * clusters->leading_dim + j] = newCentroids[k * clusters->leading_dim + j] / (double)clusters->members[k];
                }
            }

            if (fabs(SumOfDist - new_SumOfDist) < threshold) {
                endcond = 1;
                MPI_Bcast(&endcond, 1, MPI_INT, 0, MPI_COMM_WORLD);
                break;
            } else {
                MPI_Bcast(&endcond, 1, MPI_INT, 0, MPI_COMM_WORLD);
            }

            SumOfDist = new_SumOfDist;
            printf("Sum of Distances of iteration %d: %f\n", iter, new_SumOfDist);
        } else {
            part_SumOfDist = 0;
            psse = 0;

            MPI_Bcast(clusters->dataset, clusters->leading_dim * clusters->secondary_dim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            for (i = 0; i < clusters->secondary_dim; i++) {
                for (j = 0; j < clusters->leading_dim; j++) {
                    partCentroids[i * clusters->leading_dim + j] = 0;
                }
            }

            kmeans_process(data_in, clusters, partCentroids, &part_SumOfDist, &psse);
            MPI_Reduce(&part_SumOfDist, &new_SumOfDist, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Reduce(partCentroids, newCentroids, clusters->leading_dim * clusters->secondary_dim, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            MPI_Send(clusters->members, clusters->secondary_dim, MPI_UNSIGNED, 0, 5, MPI_COMM_WORLD);
            MPI_Bcast(&endcond, 1, MPI_INT, 0, MPI_COMM_WORLD);

            if (endcond)
                break;
        }
    }

    if (rank == 0) {
        MPI_Reduce(&psse, &sse, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("Finished after %d iterations\n", iter);
        printf("SSE equals to %f\n", sse);
    } else {
        MPI_Reduce(&psse, &sse, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    free(newCentroids);
    free(partCentroids);
    free(part_size);
}

void kmeans(double **data, int size, int num_attributes, int num_clusters, int max_iterations) {
    data_struct data_in;
    data_struct clusters;

    data_in.dataset = (double *)malloc(size * num_attributes * sizeof(double));
    data_in.members = (unsigned int *)malloc(size * sizeof(unsigned int));
    data_in.leading_dim = num_attributes;
    data_in.secondary_dim = size;

    clusters.dataset = (double *)malloc(num_clusters * num_attributes * sizeof(double));
    clusters.members = (unsigned int *)malloc(num_clusters * sizeof(unsigned int));
    clusters.leading_dim = num_attributes;
    clusters.secondary_dim = num_clusters;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < num_attributes; j++) {
            data_in.dataset[i * num_attributes + j] = data[i][j];
        }
    }

    for (int i = 0; i < num_clusters; i++) {
        for (int j = 0; j < num_attributes; j++) {
            clusters.dataset[i * num_attributes + j] = data[rand() % size][j];
        }
    }

    cluster(&data_in, &clusters, max_iterations);

    free(data_in.dataset);
    free(data_in.members);
    free(clusters.dataset);
    free(clusters.members);
}