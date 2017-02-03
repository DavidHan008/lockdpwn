
<Python 2.7 사용하는 함수들>


===================================================================
$ random
			seed()
            randint(0,4)        
            shuffle()
            randrange()
			sample()





===================================================================
$ time
            localtime()
            time()
			ctime()
            strftime()
            asctime()
            sleep()
			clock()



===================================================================
$ mechanize
        
        $ from mechanize import Browser
                Browser()           
                        set_handle_robots()
                        open()
                        select_form()

        


===================================================================
$ re
			compile()
			sub()


===================================================================
$ os 
            listdir()
            walk()

            path
                join()
				split()

            environ[]
        

		$ from os.path import basename
				basename()




===================================================================
$ sys
            exit(=1)
            stderr

            stdout
                write()
            stdin
                readline()
            path
                append()

            argv[]


===================================================================
$ math
            pi
            exp()



===================================================================
$ utils
            hook_container()
                            add()
            crash_binning()
            record_crash()
            crash_synopsis()




===================================================================
$ pydbg
            pydbg()
                    read_process_memory()
                    resume_all_threads()
                    enumerate_processes()
                    write_process_memory()
                    func_resolve()
                    func_resolve_debuggee()
                    terminate_process()
                    set_callback()
                    suspend_all_threads()
                    process_snapshot()
                    process_restore()
                    disasm()
                    attach()
                    bp_set()
                    replace()
                    run()
                    pid()
                    load()
                    context
                            Eip
                            Esp


        $ from pydbg.defines import *



===================================================================
$ ctypes
            windll.user32
                        SetWindowsHookExA()
                        UnhookWindowsHookEx()
                        CallNextHookEx()
                        GetMessageA()

            windll.kernel32
                        CreateProcessA()
                        CreateRemoteThread()
                        CreateRemoteThread()
                        CreateFileW()
                        CreateToolhelp32Snapshot()
                        CloseHandle()
                        ContinueDebugEvent()
                        CreateRemoteThread()
                        OpenProcess()
                        DeviceIoControl()
                        VirtualAllocEx()
                        WriteProcessMemory()
                        GetModuleHandleA()
                        GetCurrentProcessId()
                        GetProcAddress()
                        GetSystemInfo()
                        DebugActiveProcess()
                        DebugActiveProcessStop()
                        Thread32First()
                        Thread32Next()
                        WaitForDebugEvent()
                        SetThreadContext()
                        VirtualQueryEx()
                        VirtualProtectEx()
                        LoadLibrary()

            CFUNCTYPE()
            cdll.msvcrt()
                        printf()
                        strcpy()
            c_char_p()



        $ from my_debugger_defines import *
                    STARTUPINFO()
                    PROCESS_INFORMATION()
                    CREATE_NEW_CONSOLE
    

        $ from ctypes.wintypes import MSG
                    MSG()


        $ from ctypes.wintypes import DWORD




===================================================================
$ socket
                gethostbyname()
                socket()
                        bind()
                        listen()
                        accept()
                                client.recv()
                                client.sendall()

						setsockopt()
						ioctl()
						recvfrom()
                bind()
                
                AF_INET
                SOCK_RAW
                IPPROTO_IP
                IP_HDRINCL
                RCVALL_ON
                SIO_RCVALL



===================================================================
$ string
                printable()
				maketrans()

        $ from string import Template
                    Template()
                            substitute()



===================================================================
$ cgi
            FieldStorage()
                        keys()





===================================================================
$ yate
            start_response()
            include_header()
            start_form()
            para()
            do_form()
            radio_button()
            end_form()
            include_footer()
            u_list()




===================================================================
$ matplotlib
        
        $ from matplotlib.patches import FancyArrowPatch
                        __init__()
                        draw()
                        _verts3d


        $ from mpl_toolkits.mplot3d import proj3d


        
        $ import matplotlib.pyplot as plt
        $ from matplotlib import pyplot as plt
                        subplot()
                        plot()
                        ylabel()
                        title()
                        legend()
                        grid()
                        show()
                        figure()
                            scatter()
                            add_artist()
                            add_subplot()
                                    set_xlim()
                                    set_xlabel()
                                    view_init()
                                    
                            text()

                        axes()
                            plot()
                                set_data()


        $ from matplotlib import animation
                    FuncAnimation()
                                save()


===================================================================
$ pickle
            dump()
            load()

            



===================================================================
$ sqlite3
            connect()
                    cursor()
                            execute()
                                    fetchone()
                                    fetchall()
                    close()
                    commit()





========================================================================
$ immlib
            Debugger()
                    log()
                    Assemble()
                    Search()
                    Pause()
                    readMemory()
                                encode()
                    getMeomoryPagebyAddress()
                                getAccess()





===================================================================
$ android
            Android()
                    makeToast()
                    dialogCreateAlert()
                    dialogSetSingleChoiceItems()
                    dialogSetPositiveButtonText()
                    dialogSetNegativeButtonText()
                    dialogShow()
                    dialogGetResponse()
                    dialogGetSelectedItems()
                    dialogGetInput()



==================================================================
$ json
            loads()



===================================================================
$ urllib
			urlencode()

        $ from urllib import urlencode







==================================================================
$ urllib2
			Request()
			build_opener()
			HTTPCookieProcessor()



        $ from ulrlib2 import urlopen
                    urlopen()
                            read()
                                decode()
							geturl()
							getcode()
							info()

    




===================================================================
$ numpy 

        $ import numpy as np
                    linspace()
                    cos()
                    sin()
					sqrt()
					pord()
                    dot()
                    array([])
					asarray()
					zeros()
					empty()
						astype()
					ndarray
						flatten()
                  	random
						RandomState()





==================================================================
$ struct
            pack()
            unpack()





===================================================================
$ threading
            Thread()
                    setDaemon()
                    start()






==================================================================
$ getopt
            getopt()






===================================================================
$ shutil
            copy()



===================================================================
$ glob
            glob()
                




===================================================================
$ immutils
            disasmForward()
            disasmBackward() = not sure
                    getAddress()
                    analyseCode()
                    getModule()
                    Log()
                    logFunction()
                    logBaseDisplacement()
                    logRegister()
                    Hook()

            getKnowledge()
                    getAllLog()




===================================================================
$ pygame
            init()
            quit()
            Rect()

            time
                Clock()
                wait()
                delay()

            display
                flip()
                set_mode()
                set_caption()
                update()

            draw
                rect()
                circle()
                polygon()
                line()
                ellipse()

            font
                SysFont()
                render()

            event
                get()
                type
            

        $ from pygame.locals import *



===================================================================
$ argparse
            ArgumentParser()
                    add_argument()
                    parse_args()
                    print_help()




===================================================================
$ fnmatch
            fnmatch()







==================================================================
$ gzip
            open()



===================================================================
$ bz2
            BZ2File()




==================================================================
$ scipy

        $ from scipy.optimize import fsolve
                    fsolve()






===================================================================
$ sympy
            init_printing()
        
        $ import sympy as sp
                Symbol()
                sin()
                cos()
                simplify()
                pprint()
                


        $ from sympy import Matrix, solve_linear_system
                Matrix()
                    det()
                    inv()


                solve_linear_system()


        $ from sympy.abc import x,y,a,b,c,e,f,g


==================================================================
$ PIL : Python Image Library

		$ from PIL import Image
				open()
				_getexif()

		$ from PIL.ExifTags import TAGS
				






=====================================================================
$ theano : machine learning, tensor flow?

			shared()
			function()
			config
				floatX()
			tensor
				nnet
					sigmoid

		$ import theano.tensor as T
				cast()
				nnext.softmax()
				mean()
				dot()
				tanh()
				lscalar()
				matrix()
				ivector()

		$ from theano.tensor.signal import downsample


		$ from theano.tensor.nnet import conv
				conv
					conf2d()





=================================================================
$ cPickle
			dump()




=================================================================
$ nmap
			PortScanner()
				scan()
			
			all_hosts()
			all_protocols()





=================================================================
$ ftplib 
			
		from ftplib import FTP
				login()
				nlst()
				cwd()
				storbinary()




====================================================================
$ subprocess 
			call()
			check_output()
			Popen()
				stdout
					read()
				stderr
					read()





=================================================================
$ thread
			start_new_thread()






================================================================
$ zipfile
			ZipFile()
				extractall()







=================================================================
$ pyPdf
			

		$ from pyPdf import PdfFileReader
				getDocumentInfo()
				





================================================================
$ urlparse
			
		$ from urlparse import urlsplit
		






=================================================================
$ pygeoip  : IP <==> geometric 

			GeoIp()
				record_by_name()




================================================================
$ dpkt
			ethernet
				Ethernet()			
					data : ip
						data : tcp
			http
				Request()
				method
				uri
				



=================================================================
$ scapy
		
		$ from scapy.all import *
				haslayer()
				getlayer()
					seq

				sniff()
				rdpcap()
				IP()
				TCP()
				ICMP()
				send()
				sr1()

				ttl





================================================================
$ IPy
	
		$ from IPy import IP as IPTEST
				iptype()






================================================================
$ hashlib
			md5()
				hexdigest()
			sha1()
				hexdigest()








=================================================================






================================================================




================================================================



=================================================================






================================================================




================================================================



=================================================================






================================================================




================================================================



=================================================================






================================================================




================================================================



=================================================================
















