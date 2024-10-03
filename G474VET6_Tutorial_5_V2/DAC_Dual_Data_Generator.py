import numpy as np

num  = 100
low1  = 4095 * 0.1
high1 = 4095 * 0.9
low2  = 4095 * 0.3
high2 = 4095 * 0.7

ans1 = np.round(((high1 + low1) + (high1 - low1) * np.sin(2 * np.pi / num * np.arange(0, num))) / 2).astype(int)
ans2 = np.round(((high2 + low2) + (high2 - low2) * np.sin(2 * np.pi / num * np.arange(0, num) - np.pi / 2)) / 2).astype(int)
ans = (ans2 << 16) + ans1

print("const uint32_t DAC_DualData[DAC_DataSize] = {\n    ", end = "")
for i in range(num):
    print("0x%08X" % ans[i], end = ", " if ((i + 1) % 5) else (",\n    " if (i + 1 - num) else "\n};\n"))
