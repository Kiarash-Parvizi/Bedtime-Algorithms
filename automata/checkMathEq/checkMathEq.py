class Stack:
    def __init__(self):
        self.stack = []
    def __str__(self):
        return str(self.stack)
    def push(self, dataval):
        self.stack.append(dataval)
    def pop(self):
        if len(self.stack) <= 0:
            return ("No element in the Stack")
        else:
            return self.stack.pop()
    def top(self):
        return self.stack[-1]
    def size(self):
        return len(self.stack)

# format:
# !op op0 w
# w   op1 w
# *   w   *
# *   (   *
# (w  )   *

# replace operation
# ) : ) w
# ( : _
# w : op1 w
# op: w op

def check(s):
    stack = Stack()
    stack.push('s')
    for c in s:
        if c == ' ': continue
        top = stack.top()
        if top == '=':
            if c == '=' or c == '<' or c == '>': return False
            stack.pop()
        if top == '<' or top == '>':
            if c == '<' or c == '>': return False
            stack.pop()
            if c == '=': continue
        top = stack.top()
        #print(stack, ',', c)
        if c == '+' or c == '-':
            if top == 'op':
                return False
            if top == 'w':
                stack.pop()
            stack.push('op')
        elif c == '*' or c == '/' or c == '^':
            if top != 's' and top != 'w':
                return False
            stack.pop()
            stack.push('op')
        elif ((ord(c) >= ord('a') and ord(c) <= ord('z')) or
                (ord(c) >= ord('A') and ord(c) <= ord('Z')) or
                (ord(c) >= ord('1') and ord(c) <= ord('9'))):
            if top == 'op' or top == 'w':
                stack.pop()
            stack.push('w')
        elif c == '(' or c == '[':
            tmp = ')' if c == '(' else ']'
            stack.push(tmp)
        elif c == ')' or c == ']':
            #print('::', stack, ',', c)
            if top != 'w': return False
            stack.pop()
            if stack.top() != c: return False
            stack.pop()
            if stack.top() == 'op': stack.pop()
            if stack.top() != 'w':
                stack.push('w')
        elif c == '=' or c == '<' or c == '>':
            if stack.top() != 'w' or stack.size() > 2: return False
            stack.push(c)
        else: return False
    return True

s = "2x+(21)x^2+x^5 = 2 < 5x = 2x^2 > 1"
print(s, ':', check(s))
s = "c&2"
print(s, ':', check(s))
s = "[(a+b)*a] * c"
print(s, ':', check(s))
s = "(a+2)*[c]"
print(s, ':', check(s))
s = "(a+)*[c]"
print(s, ':', check(s))
s = "((a)*[c]]"
print(s, ':', check(s))
s = "a+b+c*32(1)(2c2+1(c(k(g))))(1x) < 12"
print(s, ':', check(s))
s = "[(a)*[c]]^((ab+1)/(2c(a)))"
print(s, ':', check(s))


