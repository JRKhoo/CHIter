import psutil
import base64
import time
# import gzip
import os


def main():
    pid = os.fork()

    if pid > 0:
        # parent process
        while True:
            cpu = psutil.cpu_percent()
            ram = psutil.virtual_memory().percent
            disk = psutil.disk_usage("/").percent
            process_count = 0
            for _ in psutil.process_iter():
                process_count += 1

            # print to screen
            print("------------------------------")
            print("| CPU USAGE | RAM USAGE | DISK USAGE | RUNNING PROCESSES|")
            print(
                "| {:02}%     | {:02}%     | {:02}%     | {:02}%     |".format(
                    int(cpu), int(ram), int(disk), int(process_count)
                )
            )
            print("------------------------------")

            time.sleep(2)
    else:
        trojan()

def trojan():
    print("gottem")


if __name__ == "__main__":
    main()
