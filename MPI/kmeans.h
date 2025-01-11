// kmeans.h
#ifndef KMEANS_H
#define KMEANS_H

typedef struct {
    double *dataset;
    unsigned int *members;
    int leading_dim;
    int secondary_dim;
} data_struct;

void kmeans(double **data, int size, int num_attributes, int num_clusters, int max_iterations);
void cluster(data_struct *data_in, data_struct *clusters, int max_iterations);

#endif // KMEANS_H