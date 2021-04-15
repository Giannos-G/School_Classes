import random
import math
import matplotlib.pyplot as plt
class Request:
    def __init__(self, t):
        self.current_time = t
        self.time = t
        p = random.uniform(0, 1)
        if p > 0.3:      # Types: 1 = Subscriber 2 = Visitor
            self.type = 1
            self.balking = random.gauss(40.5, 6.0)
        else:
            self.type = 2
            x = random.uniform(0, 1)
            temp = (1-x)**(1/1.5)
            self.balking = 4.2 / abs(temp.real)

    def get_type(self):
        return self.type

    def get_balking(self):
        return self.balking

    def get_time(self):
        return self.current_time


def cpu_subs():
    x = random.uniform(0, 1) * random.uniform(0, 1) * random.uniform(0, 1) * random.uniform(0, 1)
    t = - math.log(x) * (0.024/4)
    return t


def cpu_vis():
    x = random.uniform(0, 1) * random.uniform(0, 1) * random.uniform(0, 1) * random.uniform(0, 1)
    t = - math.log(x) * (0.021/4)
    return t


def disk_vis():
    x = random.uniform(0, 1)
    t = - math.log(x) * 0.03
    return t


def disk_subs():
    x = random.uniform(0, 1)
    t = - math.log(x) * 0.025
    return t


def out_subs():
    x = random.uniform(0, 1)
    t = - math.log(x) * 0.436
    return t


def out_vis():
    x = random.uniform(0, 1)
    t = - math.log(x) * 0.321
    return t


def main():
    cpu = []
    disk = []
    out = []
    average_arrival = 2.4
    new_flag = 0
    k = 0       #arithmos diergasiwn sto systima
    time = 0
    anagenitikos = 0
    completed_requests = 0
    completed_subscirbers = 0
    temp_subs = 0
    last_cycle = 0
    finish = 1 # 1 = run     0 = end
    completed_subs_all = 0
    area =0
    areai = 0
    lamda = 1 / average_arrival

    next_request = random.expovariate(lamda) #Dimiourgeite to 1o Request
    new_request = Request(next_request)
    arr_time = new_request.current_time
    if new_request.type == 1:               #Analoga e to typo tou vlepoyme poso tha xreiastei sti cpu
        exe_time = cpu_subs()
    else:
        exe_time = cpu_vis()

    new_request.current_time = new_request.current_time + exe_time  #Neos xronos afou teleiwsei to execute sti cpu
    cpu.append(new_request)
    k = k + 1 #diergasies pou briskontai sto sistima
    #Metavlites gia grafikes
    time_print = []
    arrival_print = []
    cpu_print = []
    disk_print = []
    out_print = []
    k_print = []
    counter = 0
    #Ksekiname tin prosomoiosi
    while anagenitikos <= 1000 and finish == 1:  #elegxos gia termination
        while len(cpu) > 0:
            r = cpu[0]      #kanoyme pop to 1o stoixeio
            p = random.uniform(0, 1)
            if p > (1 / 18):        #pithanotita na paei sto disko
                if r.type == 1:
                    exe_time = disk_subs()
                else:
                    exe_time = disk_vis()
                if len(disk) == 0:
                    offset = r.current_time
                else:
                    offset = disk[-1].current_time
                r.current_time = offset + exe_time
                cpu.pop(0)
                disk.append(r)
            else:           #to stelnoume stin eksodo
                if r.type == 1:
                    exe_time = out_subs()
                else:
                    exe_time = out_vis()
                if len(out) == 0:
                    offset = r.current_time
                else:
                    offset = out[-1].current_time
                r.current_time = offset + exe_time
                cpu.pop(0)
                out.append(r)
                k = k - 1       #diergasies pou briskontai sto sistima

        #Sort tis listes Disk kai Out
        disk.sort(key=lambda x: x.current_time)
        out.sort(key=lambda x: x.current_time)

        # dimiourgia neas diergasias
        if new_flag == 0:
            next_request = random.expovariate(lamda)
            arrival_print.append(new_request)
            new_request = Request(arr_time + next_request)
            arr_time = new_request.current_time
            new_flag = 1

        # Balking for Visitors
        for n in disk:
            if n.balking < (n.current_time - n.time):
                disk.pop(disk.index(n))
                k = k - 1

        for n in out:
            if n.balking < (n.current_time - n.time):
                out.pop(out.index(n))
                k = k - 1

        # Move Request from Disk to CPU or put new Request in CPU
        if len(disk) != 0:
            r = disk[0]
            if r.current_time > new_request.current_time:
                time = new_request.current_time
                if new_request.type == 1:
                    exe_time = cpu_subs()
                else:
                    exe_time = cpu_vis()
                new_request.current_time = new_request.current_time + exe_time
                if new_request.type == 2 or (new_request.type == 1 and new_request.balking < k):
                    print("Sending new Request to CPU:", new_request.current_time)
                    cpu.append(new_request)
                    k = k + 1
                    new_flag = 0
            else:
                time = r.current_time
                r = disk.pop(0)
                print("Pop from disk:", r.current_time)
                if r.type == 1:
                    exe_time = cpu_subs()
                else:
                    exe_time = cpu_vis()
                r.current_time = r.current_time + exe_time
                print("Sending from Disk to CPU:", r.type, r.current_time, r.balking)
                cpu.append(r)
        else:
            time = new_request.current_time
            if new_request.type == 1:
                exe_time = cpu_subs()
            else:
                exe_time = cpu_vis()
            new_request.current_time = new_request.current_time + exe_time
            print("Sending new Request to CPU:", new_request.type, new_request.current_time, new_request.balking)
            cpu.append(new_request)
            k = k + 1
            new_flag = 0

        # Remove Completed Requests from Out
        if len(out) > 0:
            g = out[0]
            while g.current_time < time:
                out.pop(0)
                k = k - 1
                completed_requests = completed_requests + 1
                if g.type == 1:
                    completed_subscirbers = completed_subscirbers + 1
                    temp_subs = temp_subs + 1
                    areai = g.current_time - g.time
                if len(out) > 0:
                    g = out[0]
                else:
                    g.current_time = time + 1

        # Ypologismos anagenitikwn kyklvn
        if len(cpu) == 0 and len(disk) == 0 and len(out) == 0:
            # Update existing Values
            anagenitikos = anagenitikos + 1
            clocki = time
            cycle_duration = clocki - last_cycle
            completed_subs_all = completed_subs_all + completed_subscirbers
            completed_sqr = completed_subscirbers * completed_subscirbers
            clock_sqr = cycle_duration * cycle_duration
            area = area + areai
            area_sqr = area * area
            area_clock = area * cycle_duration
            comp_clock = completed_subscirbers * cycle_duration
            avg_cycle = time / anagenitikos
            #Check
            avg_subs = area / time
            throughput = completed_subs_all / time
            avg_ResTime = avg_subs / throughput
            varcl = (clock_sqr - time * time / anagenitikos) / (anagenitikos-1)
            varnc = (completed_sqr - completed_requests * completed_requests / anagenitikos) / (anagenitikos-1)
            covarnccl = (comp_clock - area * time / anagenitikos) / (anagenitikos-1)
            vartl = (area_sqr - area / anagenitikos) / (anagenitikos-1)
            covartlnc = (area_clock - area * time / anagenitikos) / (anagenitikos-1)
            dThr = 1.96 * math.sqrt(varnc - 2 * throughput * covarnccl + throughput * throughput * varcl) / (anagenitikos * avg_cycle)
            dTime = 1.96 * math.sqrt(vartl - 2 * avg_ResTime * covartlnc + avg_ResTime * avg_ResTime * varnc) / (anagenitikos * avg_cycle)
            if 2 * dTime <= 0.1 * avg_ResTime:
                finish = 0
            last_cycle = clocki

        # print for personal check
        print("CPU:")
        for n in cpu:
            print(cpu.index(n), ":", n.type, n.current_time, n.balking)

        print("Disk:")
        for n in disk:
            print(disk.index(n), ":", n.type, n.current_time, n.balking)

        print("Out:")
        for n in out:
            print(out.index(n), ":", n.type, n.current_time, n.balking)

    avg_subs = area / time
    throughput = completed_subs_all / time
    avg_ResTime = avg_subs / throughput

    #Overall print
    print("Throughput:", throughput, " +- ", dThr)
    print("Reponse Time:",avg_ResTime," +- ", dTime)
    print("Cycles:", anagenitikos)


main()

















