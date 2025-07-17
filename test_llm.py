from openai import OpenAI
import os

client = OpenAI(
    api_key=os.environ["DEEPSEEK_API_KEY"],
    base_url="https://api.deepseek.com"
)

response = client.chat.completions.create(
    model="deepseek-chat",
    messages=[
        {"role": "system", "content": "你是一个帮助用户生成 C 语言代码的助手"},
        {"role": "user", "content": "写一个打印 Hello World 的 C 语言程序"}
    ]
)

print(response.choices[0].message.content)

