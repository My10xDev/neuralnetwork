import random
import math

x1=0.33454641946624997
x2=-0.5210491279719971
x3=-0.47183105741280906
x4=-0.15055426365707847

w1 = random.uniform(-1,1)
w2 = random.uniform(-1,1)
w3 = random.uniform(-1,1)
w4 = random.uniform(-1,1)

activation = math.tanh((x1*w1) + (x2*w2) + (x3*w3) + (x4*w4))

# Second Layer, 4 neurons, uses the activation as the x

n1_w1 = random.uniform(-1,1)
n2_w1 = random.uniform(-1,1)
n3_w1 = random.uniform(-1,1)
n4_w1 = random.uniform(-1,1)

activation_n1 = math.tanh(n1_w1*activation)
activation_n2 = math.tanh(n2_w1*activation)
activation_n3 = math.tanh(n3_w1*activation)
activation_n4 = math.tanh(n4_w1*activation)

# Next Layer

n5_w1 = random.uniform(-1,1)
n5_w2 = random.uniform(-1,1)
n5_w3 = random.uniform(-1,1)
n5_w4 = random.uniform(-1,1) 

activation_n5_a1 = math.tanh(n5_w1*activation_n1)
activation_n5_a2 = math.tanh(n5_w2*activation_n2)
activation_n5_a3 = math.tanh(n5_w3*activation_n3)
activation_n5_a4 = math.tanh(n5_w4*activation_n4)

print(activation_n5_a1)
print(activation_n5_a2)
print(activation_n5_a3)
print(activation_n5_a4)