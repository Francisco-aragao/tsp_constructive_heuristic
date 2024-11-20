import matplotlib.pyplot as plt
import numpy as np

# Data for "Primeiro nó como inicial"
instances_1 = ["att48", "berlin52", "st70", "pr76", "rat99", "kroA100", "kroB100", 
               "kroC100", "kroD100", "kroE100", "lin105", "pr124", "pr136", "pr144", 
               "kroA150", "kroB150", "pr152", "rat195", "kroA200", "kroB200"]
optimal_1 = [10628, 7542, 675, 108159, 1211, 21282, 22141, 20749, 21294, 22068, 
             14379, 59030, 96772, 58537, 26524, 26130, 73682, 2323, 29368, 29437]
cost_1 = [12861, 8980.92, 805.531, 153462, 1564.72, 26856.4, 29155, 26327.4, 
          26950.5, 27587.2, 20362.8, 69299.4, 120778, 61650.7, 33609.9, 32825.7, 
          85703, 2761.96, 35798.4, 36981.6]
time_1 = [0.001903, 0.0010034, 0.0033856, 0.0022632, 0.0043974, 0.0044204, 
          0.0043634, 0.0044004, 0.0044182, 0.0043896, 0.00492, 0.0072172, 
          0.009604, 0.010979, 0.0118756, 0.0121312, 0.01233, 0.0226642, 
          0.0241298, 0.0243252]

# Data for "Nó central inicial"
cost_2 = [12964, 9140.13, 783.72, 151142, 1493.92, 25781.6, 27208.5, 24173.9, 
          27695.5, 26884.6, 19182.4, 68321.4, 116045, 64161.5, 32786.8, 34583.7, 
          80161.3, 2830.1, 37701.5, 36893.6]
time_2 = [0.0019, 0.0010, 0.002179, 0.0024008, 0.0043878, 0.0044748, 
          0.0046738, 0.0045104, 0.004607, 0.0045522, 0.005191, 0.0074482, 
          0.0098506, 0.011302, 0.0123896, 0.0124628, 0.0128008, 0.0231814, 
          0.0246762, 0.024664]

# Plot 1: Histogram of solution costs compared to optimal
x = np.arange(len(instances_1))  # X-axis positions

plt.figure(figsize=(12, 6))
width = 0.35  # Bar width

# Bar plot for solutions
plt.bar(x - width / 2, cost_1, width, label='Primeiro nó como inicial', color='blue', alpha=0.7)
plt.bar(x + width / 2, cost_2, width, label='Nó central inicial', color='orange', alpha=0.7)

# Add optimal as a line
plt.plot(x, optimal_1, label='Ótimo', color='green', marker='o', linestyle='dashed')

# Labels and legend
plt.xticks(x, instances_1, rotation=90)
plt.xlabel("Instância")
plt.ylabel("Custo")
plt.title("Comparação dos Custos (Soluções vs Ótimo)")
plt.legend()
plt.tight_layout()
plt.show()

# Plot 2: Histogram of execution times
plt.figure(figsize=(12, 6))

# Bar plot for execution times
plt.bar(x - width / 2, time_1, width, label='Primeiro nó como inicial', color='blue', alpha=0.7)
plt.bar(x + width / 2, time_2, width, label='Nó central inicial', color='orange', alpha=0.7)

# Labels and legend
plt.xticks(x, instances_1, rotation=90)
plt.xlabel("Instância")
plt.ylabel("Tempo (s)")
plt.title("Comparação dos Tempos de Execução")
plt.legend()
plt.tight_layout()
plt.show()