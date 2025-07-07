

from openai import OpenAI
import os


def ask_llm(
  *,
  system_prompt,
  user_prompt,
  model_version="v3",
) -> str:
  client = OpenAI(api_key=os.environ["DEEPSEEK_API_KEY"],
                  base_url="https://api.deepseek.com")

  model = "deepseek-chat" if model_version == "v3" else "deepseek-chat"

  response = client.chat.completions.create(
    model=model,
    messages=[
      {
        "role": "system",
        "content": system_prompt
      },
      {
        "role": "user",
        "content": user_prompt
       },
    ],
    stream=False
  )

  return response.choices[0].message.content
