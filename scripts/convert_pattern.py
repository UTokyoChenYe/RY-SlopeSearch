# === convert_patterns.py ===
# 功能：将输入的 R/Y 模式全部转为小写，并加上引号与逗号，然后保存到 .txt 文件中
# 作者：陈晔
# 日期：自动生成

import os

# === 输入字符串 ===
input_text = """
RRRRRRRYYRYY RRYRRYYYYYYY
RRRRRRYYYRYY RRYRRRYYYYYY
RRRRRYRYYRYY RRYRRYRYYYYY
RRRRRYYRYRYY RRYRYRRYYYYY
RRRRRYYYYRYY RRYRRRRYYYYY
RRRRYRYYYRYY RRYRRRYRYYYY
RRRRYYYRRYYY RRRYYRRRYYYY
RRRRYYYRYRYY RRYRYRRRYYYY
RRRYRRRYYRYY RRYRRYYYRYYY
RRRYRYRYYRYY RRYRRYRYRYYY
RRRYRYYRRYYY RRRYYRRYRYYY
RRRYRYYRYRYY RRYRYRRYRYYY
RRRYYRRYYRYY RRYRRYYRRYYY
RRRYYRYRYRYY RRYRYRYRRYYY
RRYRRRRYYRYY RRYRRYYYYRYY
RRYRRYYRYRYY RRYRYRRYYRYY
"""

# === 处理 ===
patterns = input_text.split()  # 按空格和换行分割
converted = [f'"{p.lower()}",' for p in patterns]  # 转小写并加引号与逗号

# === 输出到文件 ===
output_path = os.path.join(os.getcwd(), "converted_patterns.txt")

with open(output_path, "w", encoding="utf-8") as f:
    for i in range(0, len(converted), 10):  # 每行 10 个，方便查看
        f.write(" ".join(converted[i:i+10]) + "\n")

print(f"✅ 已成功生成文件：{output_path}")

