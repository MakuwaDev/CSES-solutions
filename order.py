import requests
from bs4 import BeautifulSoup

URL = "https://cses.fi/problemset/list/"
BASE_URL = "https://cses.fi"

def fetch_tasks():
    response = requests.get(URL)
    response.raise_for_status()

    soup = BeautifulSoup(response.text, "html.parser")
    tasks = []

    for li in soup.find_all("li", class_="task"):
        a_tag = li.find("a")
        detail_span = li.find("span", class_="detail")

        if not a_tag or not detail_span:
            continue

        name = a_tag.text.strip()
        link = BASE_URL + a_tag["href"]
        detail_text = detail_span.text.strip()

        x_str = detail_text.split("/")[0].strip()
        try:
            x_value = int(x_str)
        except ValueError:
            continue

        tasks.append((x_value, name, detail_text, link))

    return tasks


def main():
    tasks = fetch_tasks()

    tasks.sort(key=lambda t: t[0], reverse=True)

    with open("cses_tasks.txt", "w", encoding="utf-8") as f:
        for _, name, detail_text, link in tasks:
            f.write(f"{name} | {detail_text} | {link}\n")

    print(f"Saved {len(tasks)} tasks to cses_tasks.txt")


if __name__ == "__main__":
    main()