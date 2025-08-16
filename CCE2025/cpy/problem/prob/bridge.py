#!/usr/bin/env python3
import sys
import os
import base64
import uuid
import tempfile

filename = str(uuid.uuid4())

def write(x):
    sys.stdout.write(x)
    sys.stdout.flush()

def readline():
    write("> ")
    return sys.stdin.readline().rstrip("\n")

def bridge():
    write("[+] Input Base64 encoded Python file\n")
    data = readline()

    if not data:
        write("[-] Error!\n")
        exit()

    try:
        python_code = base64.b64decode(data).decode('utf-8')
    except:
        write("[-] decode error!\n")
        exit()

    write("[+] Copying Python file ..\n")
    workdir = "/tmp/%s" % filename
    os.mkdir(workdir)
    
    # Write Python code with sandbox enabled
    with open(workdir + "/exploit.py", "w") as f:
        f.write(f"""import sandbox
sandbox.enable()

{python_code}
""")
    
    return workdir

def run(workdir):
    try:
        write("[+] Setting up Environment ..\n")
        os.chdir(workdir)
        
        os.environ['PYTHON_OPT_LEVEL'] = '1'
        os.environ['PYTHONPATH'] = '/home/ctf/prob/lib/python3.13/site-packages'
        os.environ['PATH'] = '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/ctf/prob/bin:/home/ctf/prob/bin'
        
        write("[+] Executing Python code ..\n")
        os.system('/home/ctf/prob/bin/python3 exploit.py')
        
        write("Done!\n")
        os.system(f"rm -rf {workdir}")
        exit()
    except:
        os.system(f"rm -rf {workdir}")
        exit()

if __name__ == "__main__":
    run(bridge())
