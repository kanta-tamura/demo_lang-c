# demo-lang

toy programing language

## build setup

print token to stdout

```bash
> make

> make run ARG=pro1.demo
```

## token kind

### keyword

```
"begin", "end", "if", "then", "while", "do", "return",
"function", "var", "const", "odd", "write", "writeln",
```

### punctuators

```
"+", "-", "*", "/", "(", ")", "=", "<", ">",
"<>", "<=", ">=", ",", ".", ";", ":=",
```

### identifier

```
ident := [a-z|A-Z]+ [0-9]*
```

### Numeric literals

```
num := [0-9]+
```
