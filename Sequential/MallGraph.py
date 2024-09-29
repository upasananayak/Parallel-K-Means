import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Load the full dataset, but select only the "Annual Income" and "Spending Score" columns
df = pd.read_csv("Mall_Customers.csv")
df = df[["Annual Income (k$)", "Spending Score (1-100)"]]

# Before clustering
sns.scatterplot(x=df["Annual Income (k$)"], 
                y=df["Spending Score (1-100)"])
plt.title("Scatterplot of spending (y) vs income (x)")
plt.xlabel("Annual income (k$)")
plt.ylabel("Spending Score (1-100)")
plt.show()

# After clustering
plt.figure()
df_clustered = pd.read_csv("output1.csv")
sns.scatterplot(x=df_clustered.x, y=df_clustered.y, 
                hue=df_clustered.c, 
                palette=sns.color_palette("hls", n_colors=5))
plt.xlabel("Annual income (k$)")
plt.ylabel("Spending Score (1-100)")
plt.title("Clustered: spending (y) vs income (x)")
plt.show()
