'''
    python ==> my_debugger.py 를 사용해본 예제 코드인듯
'''
import my_debugger

debugger = my_debugger.debugger()


pid = raw_input("Enter the PID if the process to attach to: ")

debugger.attach(int(pid))

debugger.run()

debugger.detach()

