def sol(s, t):
    n = len(s)
    lst = [0]*26
    vo = 0
    co = 0
    maxvo = 0
    maxco = 0

    for i in s:
        lst[ord(i) - 65] = lst[ord(i) - 65] + 1
        if i == 'A' or i == 'E' or i == 'I' or i == 'O' or i == 'U':
            vo += 1
            if maxvo < lst[ord(i) - 65]:
                maxvo = lst[ord(i) - 65]
        else:
            co += 1
            if maxco < lst[ord(i) - 65]:
                maxco = lst[ord(i) - 65]

    ans1 = (2*(vo - maxvo)) + co
    ans2 = (2*(co - maxco)) + vo

    if ans1 > ans2:
        print("Case #{}: {}".format(t, ans2))
    else: print("Case #{}: {}".format(t, ans1))


if __name__ == '__main__':
    q = int(input())
    t = 1
    while(t <= q):
        s = input()
        sol(s, t)
        t += 1