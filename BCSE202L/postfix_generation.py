def generatePostfix(infix) -> str:
    operators_stack = list()
    infix = infix.replace(" ", "")
    postfix = ""
    operators = {
        "^": 3,
        "*": 2,
        "/": 2,
        "+": 1,
        "-": 1
    }
    for token in infix:
        if token == "(":
            operators_stack.append(token)
        elif token == ")":
            while operators_stack[-1] != "(":
                postfix += operators_stack.pop()
            operators_stack.pop()
        elif token in operators:
            while len(operators_stack) > 0 and operators_stack[-1] != "(" and operators[token] <= operators[operators_stack[-1]]:
                postfix += operators_stack.pop()
            operators_stack.append(token)
        else:
            postfix += token
    while len(operators_stack) > 0:
        postfix += operators_stack.pop()
    return postfix

print(generatePostfix("a+b*(c^d-e)^(f+g*h)-i"))
# Output: abcd^e-fgh*+^*+i-