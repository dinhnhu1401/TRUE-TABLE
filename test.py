import ttg
# print(ttg.Truths(['p', 'q', 'r']))
print(ttg.Truths(['t', 'q', 'p', 'z', 'u'],['z = u','t or q', '~p', '(t or q) and ~p', 'u or q', 'z => (u or q)', '(((t or q) and ~p) => (z => (u or q)))']))


# ((tvq)^~p)->(z->(uvq))