st = "!d ^ s > t;d > c"
sd = "!d ^ s ; t"


# kiểm tra xem mệnh đề có phép kéo theo?
def check(phrase):
    if ">" in phrase:
        return True
    return False  #


# thêm phủ định vào biến
def negative(var):
    if var[0:1] == "!":
        return var.replace("!", "")
    else:
        return "!" + var


# chuyển đổi dùng luật De Morgan
def DeMorgan(phrase):
    tmp = []
    sign = 0
    for var in phrase.split(" "):
        if var == ">":  # những biến sau phép kéo theo không cần thêm phủ
            sign = 1
        if sign == 0 and var != "^":  # những biến trước đó thì cần thêm phủ
            tmp.append(negative(var))
        if sign == 1 and var != ">":
            tmp.append(var)
    return tmp


# thêm phủ khi chuyển vế
def trans(phrase):
    tmp = []
    for i in phrase:
        tmp.append(negative(i))
    return tmp


# kiểm tra xem có đối ngẫu?
def match(a, b):
    for x in a:
        for y in b:
            if x == y or x == negative(y):
                a.remove(x)
                b.remove(y)
                c=a+b
    return c


# nhâp & chuyển tất cả về dạng chuẩn
def std(inp):
    # inp = input()

    global temp2
    global temp1

    lst = inp.split(";")
    left = lst[0].split(",")  # mặc định GT là right
    right = lst[1].split(",")  # KL là left
    for phrase1 in left:
        temp1 = []
        if check(phrase1):  # kiểm tra xem có cần dùng
            temp1 = DeMorgan(phrase1)  # luật De Morgan
        else:
            for letter in phrase1:  # nếu ko cần thì loại bỏ
                if letter != "^":  # "^" và thêm vào líst temp1
                    temp1.append(letter)
        left.remove(phrase1)
        left.append(temp1)

    for phrase2 in right:  # De Morgan cho KL và đổi vế
        temp2 = []
        if check(phrase2):
            temp2 = DeMorgan(phrase2)
        else:
            for letter in phrase2.split(" "):  # nếu ko cần thì loại bỏ
                if letter != "v":  # "v" và thêm vào líst temp1
                    temp2.append(letter)
        right.remove(phrase2)
        right.append(temp2)
        left.append(trans(temp2))
    return right, left


def Robinson():
    lst = std()
    for elem in range(len(lst)):

