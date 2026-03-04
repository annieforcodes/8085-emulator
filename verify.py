import subprocess
import json
import random

Numoftest = 1000 #edit as you want
Numoftest_sub = 1500
all_passed = True #tracks if all add cases passed
all_passed_sub = True 
#add
for i in range(Numoftest):

    a = random.randint(0,255) #8bits
    b = random.randint(0,255)

    with open("program.hex", "w") as f:
        f.write(f"3E {a:02X}\n") #mvi a
        f.write(f"06 {b:02X}\n") #mvi b
        f.write("80\n") #add b
        f.write("76\n") #hlt

    result = subprocess.run(["./emulator","program.hex"],capture_output=True, text=True)
    cpu = json.loads(result.stdout.strip())

    expected = (a+b) & 0xFF
    expected_cy = 1 if (a+b) >255 else 0
    expected_z = 1 if expected ==0 else 0
    expected_s = 1 if (expected & 0x80) else 0 #first bit 1 ->mask = 1000 0000

    if cpu["A"] != expected :
        print(f"FAIL: A mismatches for (a = {a}, b= {b})")
        all_passed = False
        break
    if cpu["CY"] != expected_cy :
         print(f"FAIL: CY mismatches for (a = {a}, b= {b})")
         all_passed = False
         break
    if cpu["Z"] != expected_z :
        print(f"FAIL: Z mismatches for (a = {a}, b= {b})")
        all_passed = False
        break
    if cpu["S"] != expected_s :
        print(f"FAIL: S mismatches for (a = {a}, b= {b})")
        all_passed = False
        break
if all_passed:
    print(f"all {Numoftest} ADD test cases passed!!!")

#sub
for i in range(Numoftest_sub):

    a = random.randint(0,255)
    b = random.randint(0,255)

    with open("program.hex", "w") as f:
        f.write(f"3E {a:02X}\n")  # MVI A
        f.write(f"06 {b:02X}\n")  # MVI B
        f.write("90\n")           # SUB B
        f.write("76\n")           # HLT

    result = subprocess.run(["./emulator","program.hex"], capture_output=True, text=True)
    cpu = json.loads(result.stdout.strip())

    expected = (a - b) & 0xFF
    expected_cy = 1 if a < b else 0
    expected_z = 1 if expected == 0 else 0
    expected_s = 1 if (expected & 0x80) else 0

    if cpu["A"] != expected:
        print(f"FAIL SUB: A mismatch (a={a}, b={b})")
        all_passed_sub = False
        break

    if cpu["CY"] != expected_cy:
        print(f"FAIL SUB: CY mismatch (a={a}, b={b})")
        all_passed_sub = False
        break

    if cpu["Z"] != expected_z:
        print(f"FAIL SUB: Z mismatch (a={a}, b={b})")
        all_passed_sub = False
        break

    if cpu["S"] != expected_s:
        print(f"FAIL SUB: S mismatch (a={a}, b={b})")
        all_passed_sub = False
        break
if all_passed_sub:
    print(f"All {Numoftest_sub} SUB tests passed!")