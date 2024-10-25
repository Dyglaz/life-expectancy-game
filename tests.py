import subprocess


def process(command):
    return subprocess.Popen(
        command.split(),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        stdin=subprocess.PIPE,
        shell=True
    )


def expect(proc, pattern):
    pattern = pattern.strip("\n")
    buffer = ""
    while True:
        buffer += proc.stdout.read(1).decode()
        if pattern.endswith(buffer):
            return True


def write(proc, text):
    proc.stdin.write(f'{text}\n'.encode())
    proc.stdin.flush()
    return text


def test():
    print("Launching processes")
    try:
        c_process = process('life-expectancy.exe')
        bas_process = process('life-expectancy.bas')  

        expected_greetings = '''
                     LIFE EXPECTANCY
                    CREATIVE COMPUTING
                  MORRISTOWN, NEW JERSEY


THIS IS A LIFE EXPECTANCY TEST.
   DO YOU WISH INSTRUCTIONS? 
'''
        print("Expecting greetings...")
        expect(bas_process, expected_greetings)
        expect(c_process, expected_greetings)
        print("[+] TEST 1 - PASSED")

        print("Sending keys...")
        write(c_process, 'Y')
        write(bas_process, 'Y')
        print("[+] KEYS SENT")

        instruction = '''
THIS IS A TEST TO PREDICT YOUR LIFE EXPECTANCY.  I
WILL ASK YOU A SERIES OF SHORT QUESTIONS, WHICH YOU WILL
REPLY BY TYPING IN THE CORRESPONDING ANSWER TO THE
QUESTION.

        EXAMPLE:  WHAT IS YOUR SEX?
               M=MALE
               F=FEMALE
'M' AND 'F' ARE THE POSSIBLE REPLIES TO THE QUESTION, ANSWER
LIKE THIS:
              CHOOSE ONE OF THE LETTERS ABOVE? M
TYPING AN 'M' SIGNIFIES YOU ARE A MALE. 



'''
        expect(bas_process, instruction)
        expect(c_process, instruction)
        print("[+] TEST 2 - PASSED")

        # Пример вопросов и ответов
        test_values = [
            ('M', 'M'),  # Пол
            ('G', 'G'),  # Место жительства
            ('M', 'M'),  # Как работаете
            ('F', 'F'),  # Как часто упражняетесь
            ('N', 'N'),  # С кем живете
            ('I', 'I'),  # Спите более 10 часов
            ('L', 'L'),  # Психическое состояние
            ('J', 'J'),  # Счастливы или нет
            ('H', 'H'),  # Штраф за превышение скорости
            ('G', 'G'),  # Доход
            ('J', 'J'),  # Образование
            ('L', 'L'),  # Возраст
            ('K', 'K'),  # Наследственность
            ('E', 'E'),  # Родители
            ('M', 'M'),  # Болезни в семье
            ('C', 'C'),  # Курение
            ('H', 'H'),  # Алкоголь
            ('A', 'A'),  # Вес
            ('K', 'K'),  # Проверки
            ('K', 'K'),  # Гинеколог
            ('L', 'L'),  # Текущий возраст
        ]

        for i, (response_c, response_bas) in enumerate(test_values):
            print(f"Sending response for question {i + 1}...")
            write(c_process, response_c)
            write(bas_process, response_bas)
            print("[+] KEYS SENT")
            if i != 20:
                question_prompt = 'CHOOSE ONE OF THE LETTERS ABOVE? '
                expect(c_process, question_prompt)
                expect(bas_process, question_prompt)
                print(f"[+] TEST {i + 3} - PASSED")

        final_result = '''
YOU ARE EXPECTED TO LIVE TO THE AGE OF 65 YEARS
OUT LIVING 36% OF THE MEN AND 20% OF THE WOMEN. 
'''
        expect(c_process, final_result)
        expect(bas_process, final_result)
        print("[+] TEST FINAL - PASSED")

    except Exception as ex:
        print(ex)

test()
