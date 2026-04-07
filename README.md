# Tokenizers

Simple code to test:

```
TokenizerBPE bpe("hugging_face_llama3.2_tokenizer.json");
bpe.Load();
auto ids = bpe.Encode("Hello! Briefly explain what car is.\n");
```

In `test_data` are some pre-generated strings and their token ids, which are taken from grount-truth HuggingFace tokenizer.

Note: parts of the code were written by Codex, since I did not have time to study how exactly tokenizers work. U just wanted to test hashed version of lookups and add some optimizations to token generation.
