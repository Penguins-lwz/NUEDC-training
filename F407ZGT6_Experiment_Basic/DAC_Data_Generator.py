import numpy as np

num  = 30
low  = 0.5 / 3.3 * 4096
high = 2.5 / 3.3 * 4096

ans = np.round(((high + low) + (high - low) * np.sin(2 * np.pi / num * np.arange(0, num))) / 2).astype(int)

print("const uint16_t DAC_Data[DAC_DataSize] = {\n    ", end = "")
for i in range(num):
    print("0x%03X" % ans[i], end = ", " if ((i + 1) % 10) else (",\n    " if (i + 1 - num) else "\n};\n"))
