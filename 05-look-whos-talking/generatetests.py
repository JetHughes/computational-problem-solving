import json

with open('data.json', 'r',encoding='utf-8') as f:
  data_str = f.read()
data = json.loads(data_str)

def get_participle(subject):
  participle = None
  if "We" in subject or "You" in subject or "They" in subject: 
    participle = "are"
  elif "He" in subject or "She" in subject: 
    participle = "is"
  elif subject == "I": 
    participle = "am"
  return participle

def valid_sentences():
  sentences = []
  for subject in data ["subjects_english"]:
    for verb in data["verbs"]:    
      # past     
      english = f"{subject} {verb['english_past']}"
      māori = f"I {verb['māori']} {data['subjects_dict'][str.lower(subject)]}"
      sentences.append(f"{english}, {māori}")

      # present
      english = f"{subject} {get_participle(subject)} {verb['english_present']}"
      māori = f"Kei te {verb['māori']} {data['subjects_dict'][str.lower(subject)]}"
      sentences.append(f"{english}, {māori}")

      # future
      english = f"{subject} {verb['english_future']}"
      māori = f"Ka {verb['māori']} {data['subjects_dict'][str.lower(subject)]}"
      sentences.append(f"{english}, {māori}")
  return sentences

def main():
  for sentence in valid_sentences():
    print(sentence)

if __name__ == "__main__":
  main()