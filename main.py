import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import time 
import os
def clear_console():
            os.system('cls' if os.name == 'nt' else 'clear')
def mainScreen():
    print('===============================================')
    print('||                                           ||')
    print('||                Welcome to                 ||')
    print('||              AnyName Banking              ||')
    print('||                                           ||')
    print('||               What can we do              ||')
    print('||               for you today?              ||')
    print('||                                           ||')
    print('||                                           ||')
    print('||       1. Withdraw     3.Balance           ||')
    print('||       2. Deposit      4.Exit and Close    ||')
    print('||                                           ||')
    print('===============================================')
    userinput = int(input())

    if userinput == 1:
        print('===============================================')
        print('||                                           ||')
        print('||                Welcome to                 ||')
        print('||              AnyName Banking              ||')
        print('||                                           ||')
        print('||               You selected:               ||')
        print('||                Withdrawal                 ||')
        print('||                                           ||')
        print('||           Is this correct? (Y/N)          ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('===============================================')
        yes_no = str(input(''))
        
        ##if yes_no == 'Y':
        clear_console()


    if userinput == 2:
        print('===============================================')
        print('||                                           ||')
        print('||                Welcome to                 ||')
        print('||              AnyName Banking              ||')
        print('||                                           ||')
        print('||               You selected:               ||')
        print('||                  Deposit                  ||')
        print('||                                           ||')
        print('||           Is this correct? (Y/N)          ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('===============================================')
        yes_no = str(input(''))

        ##if yes_no == 'Y'
        clear_console()
    if userinput == 3:
        print('===============================================')
        print('||                                           ||')
        print('||                Welcome to                 ||')
        print('||              AnyName Banking              ||')
        print('||                                           ||')
        print('||               You selected:               ||')
        print('||               Balance Check               ||')
        print('||                                           ||')
        print('||           Is this correct? (Y/N)          ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('===============================================')
        yes_no = str(input(''))
    if userinput == 4:
        print('===============================================')
        print('||                                           ||')
        print('||           Thank you for using             ||')
        print('||             AnyName Banking               ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('||                                           ||')
        print('===============================================')
        time.sleep(5)
        clear_console()
        mainScreen()
        
mainScreen()