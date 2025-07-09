

from openai import OpenAI
import os


def ask_llm(
  *,
  system_prompt,
  user_prompt,
  model_version="dpsk-v3",
) -> str:
  if model_version == "dpsk-v3":
    client = OpenAI(api_key=os.environ["DEEPSEEK_API_KEY"],
                    base_url="https://api.deepseek.com")

    model = "deepseek-chat"
  elif model_version == "dpsk-r1":
    client = OpenAI(api_key=os.environ["DEEPSEEK_API_KEY"],
                    base_url="https://api.deepseek.com")

    model = "deepseek-reasoner"
  elif model_version == "claude":
    client = OpenAI(api_key=os.environ["CLAUDE_API_KEY"],
                    base_url="https://chat.cloudapi.vip/v1")
    model = "claude-3-7-sonnet-20250219"  # or "gpt-4" if available
  else:
    raise ValueError(f"Unsupported model version: {model_version}")

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
