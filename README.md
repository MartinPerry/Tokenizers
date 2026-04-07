# Tokenizers

Simple code to test:

```
TokenizerBPE bpe("hugging_face_llama3.2_tokenizer.json");
bpe.Load();
auto ids = bpe.Encode("Hello! Briefly explain what car is.\n");
```
