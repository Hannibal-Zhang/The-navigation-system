#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/***
第一题部分：
根据输入的n个车站，创建n个35位（站名最长为31）的数组。
根据输入的m个schedule，创建m个schedule统计，每条schedule最多为K个stop
根据From To 以及Depart at,遍历查询每条schedule，判断在一条schedule是否可以满足从From stop 到To stop并且时间也满足
最差的情况，需要遍历所有的schedule的所有stop，因为每个schedule最多为k个stop，所以时间复杂度为 O(m * k)
第二题部分：
 In the Queries function, the outermost while loop is used. The maximum number of while
 loops is to traverse each site once, that is, n times, while multiple second-level for loops
 are nested in the while loop. Four for loops, each of which will have an operation to find a
 line, so the maximum complexity of the first four for loops is O(n·k^2); for the following
 for loops, if there is no need to transfer , The maximum complexity of each for loop to
 traverse all the lines is O(n·k^2), if you need to transfer, the maximum complexity is
 O(n·(k + k)^2); So time complexity of the Queries function is O(4·n·k^2) = O(n·k^2);
 但是由于第二题并没有完成，所以还没有调用第二题的Queries function。
 总结：
 该程序的时间复杂度为 O(m * k)。
 ***/


int getIntTime(char timeStr[5]) {  //将类似于0910的四位时间字符串转换为int表示
    return (timeStr[3] - '0') + (timeStr[2] - '0') * 10 + (timeStr[1] - '0') * 60 + (timeStr[0] - '0') * 600;
}

void getStrTime(int time) {  // 将int形式的时间表示转换为字符串方便输出
   char timeStr[5];  // 定义5位，因为有一位放\0
   char zero = '0';
   int hour = time/60;
   int minute = time % 60;
   timeStr[0] = hour/10 + zero;
   timeStr[1] = hour%10 + zero;
   timeStr[2] = minute/10 + zero;
   timeStr[3] = minute%10 + zero;
   timeStr[4] = '\0';
   printf("%s ", timeStr);
}

// 查询路线，查找不到输出no found
void findWay(char **stops,int stopSum, int numbers, int **indexs, int **times) {
    int i, j, k, x, y, z;
    char nameStr[35]; 
    char timeStr[5];
    while(1) {
        printf("From: ");
        scanf("%s", nameStr);
        int f=-1;  // 初始化一个是否找到起始站的索引值
        for (i=0;i<stopSum;i++) {
             if (strcmp(stops[i], nameStr) == 0) {  // 对比寻找输入的站点和所有的站点
                 f = i + 1;
                 break;
             }
        } 
        if (f == -1) {  // 如果一直没找到输入的站点，就终止
            printf("Thank you for using goNSW.\n");
            break;
        }
        printf("To: ");
        scanf("%s", nameStr);
        int t = -1;  // 初始化一个是否找到终点站的索引值
        for (i=0;i<stopSum;i++) {
             if (strcmp(stops[i], nameStr) == 0) {  // 对比寻找输入的终点站和所有的站点
                 t = i + 1;
                 break;
             }
        } 
        printf("Depart at: ");  // 获取输入的出发时间
        scanf("%s", timeStr);
        int timeInt = getIntTime(timeStr);  // 把出发时间转换成int型
        z = 0;
        for (i=0;i<numbers;i++) {
            x = -1;  // 初始化找到出发站和终点站的索引
            y = -1;
            for(j=0;j<stopSum;j++) {
                if (indexs[i][j] == f && times[i][j] >= timeInt) {  // 找到和出发站一致的索引值，时间也符合要求
                    x = j;
                }
                if (indexs[i][j] == t) {  // 找到和终点站一致的索引
                    y = j;
                }
                if (x >= 0 && y >= 0) {  // 如果出发和终点都找到了
                    z = 1;
                    printf("\n");
                    for (k=x;k<=y;k++) {
                        getStrTime(times[i][k]);  // 把时间再转换成字符串并输出
                        printf("%s\n", stops[indexs[i][k]-1]);  // 同时输出对应的站点名字
                    }
                    printf("\n");
                    break;
                }
            }
            if (z == 1) {  // 如果已经找到了两个站点，就不用继续往下找了
                break;
            }
        }
        if (z == 0) {  // 如果遍历完还没有找到两个站点，就是找不到连接
            printf("\nNo connection found.\n");
        }
    }
}

void Queries(int nb_of_stop, int nb_of_step, int number_of_stations, char *stop_time_table_1[],
             char *all_time_stops_1[], char *stop_time_table_2[], char *all_time_stops_2[]) {

    char *from_stop_str;
    char *to_stop_str;
    char *depart_time_str;
    from_stop_str = (char *) malloc(32 * sizeof(char));
    assert(from_stop_str != NULL);
    to_stop_str = (char *) malloc(32 * sizeof(char));
    assert(to_stop_str != NULL);
    depart_time_str = (char *) malloc(5 * sizeof(char));
    assert(depart_time_str != NULL);

    //Initialize a loop condition, and then match the termination condition to forcefully terminate the loop
    int m = 1;
    while (m) {
        printf("\n");
        printf("From: ");
        scanf("%s", from_stop_str);
        if (strcmp(from_stop_str, "done") != 0) {  // If the start station entered is not the ‘done’ entered, continue
            printf("To: ");
            scanf("%s", to_stop_str);
            printf("Depart at: ");
            scanf("%s", depart_time_str);
            printf("\n");

            int start_1 = number_of_stations;  // Initialize the start and end points of the first line
            int end_1 = number_of_stations;
            char *find_stop_1;
            find_stop_1 = (char *) malloc(32 * sizeof(char));
            assert(find_stop_1 != NULL);
            char *find_time_1;
            find_time_1 = (char *) malloc(5 * sizeof(char));
            assert(find_time_1 != NULL);

            for (int w1 = 0; w1 < nb_of_stop; w1++) {  // Traverse all the stations in the first line
                // timetable and find the index position consistent
                // with the input starting station
                strcpy(find_stop_1, all_time_stops_1[w1]);
                strcpy(find_time_1, stop_time_table_1[w1]);
                if (strcmp(find_stop_1, from_stop_str) == 0) {  // Found the start site
                    if (strcmp(find_time_1, depart_time_str) >= 0) {  // The time of the start station
                        // meets the conditions
                        start_1 = w1;
                        break;
                    }
                }
            }
            char *end_time_1;
            end_time_1 = (char *) malloc(5 * sizeof(char));
            assert(end_time_1 != NULL);
            for (int w2 = 0; w2 < nb_of_stop; w2++) {  // Traverse all the stations in the first line timetable
                // and find the index position consistent with the input
                // stop station
                strcpy(find_stop_1, all_time_stops_1[w2]);
                if (strcmp(find_stop_1, to_stop_str) == 0) {
                    strcpy(end_time_1, stop_time_table_1[w2]);  // Record the arrival time of the first line to
                    // facilitate the comparison of the second question
                    end_1 = w2;
                    break;
                }
            }

            int start_2 = number_of_stations;
            int end_2 = number_of_stations;
            char *find_stop_2;
            find_stop_2 = (char *) malloc(32 * sizeof(char));
            assert(find_stop_2 != NULL);
            char *find_time_2;
            find_time_2 = (char *) malloc(5 * sizeof(char));
            assert(find_time_2 != NULL);
            for (int w3 = 0; w3 < nb_of_step; w3++) {  // Traverse all the stations in the second line timetable,
                // find the index position consistent with the input
                // starting station
                strcpy(find_stop_2, all_time_stops_2[w3]);
                strcpy(find_time_2, stop_time_table_2[w3]);
                if (strcmp(find_stop_2, from_stop_str) == 0) {  // Found the start site
                    if (strcmp(find_time_2, depart_time_str) >= 0) {  // The time of the start station
                        // meets the conditions
                        start_2 = w3;
                        break;
                    }
                }
            }
            char *end_time_2;
            end_time_2 = (char *) malloc(5 * sizeof(char));
            assert(end_time_2 != NULL);
            for (int w4 = 0; w4 < nb_of_step; w4++) {  // Traverse all the stations in the second line timetable
                // and find the index position consistent with the input
                // termination station
                strcpy(find_stop_2, all_time_stops_2[w4]);
                if (strcmp(find_stop_2, to_stop_str) == 0) {
                    strcpy(end_time_2, stop_time_table_1[w4]);  // Record the arrival time of the second line to
                    // facilitate the second question comparison
                    end_2 = w4;
                    break;
                }
            }

            char *change_stop_1;
            change_stop_1 = (char *) malloc(32 * sizeof(char));
            assert(change_stop_1 != NULL);
            char *change_stop_2;
            change_stop_2 = (char *) malloc(32 * sizeof(char));
            assert(change_stop_2 != NULL);

            int start_1_1 = start_1;
            int start_2_2 = start_2;
            if (start_1 < number_of_stations) { // Starting stop is on the first line
                if (end_1 < number_of_stations && end_2 < number_of_stations) { // The end stop is on both the
                    // first and second lines
                    if (strcmp(end_time_1, end_time_2) < 0) { //If the first line arrives early, it will output directly
                        if (start_1 < end_1) {
                            for (start_1_1; start_1_1 <= end_1; start_1_1++) {
                                printf("%s ", stop_time_table_1[start_1_1]);
                                printf("%s\n", all_time_stops_1[start_1_1]);
                            }
                            continue;
                        }
                    } else if (strcmp(end_time_1, end_time_2) > 0) {
                        //The second line arrives early, see if there is a connection stop between the two lines
                        char connect_stop = 0;
                        if (connect_stop != -1) {  // There is a connection stop between the two lines
                            int change_index_1 = -1;
                            int change_index_2 = -1;
                            for (int w5 = 0; w5 < end_1; w5++) {  // Find the index value of the connection stop
                                strcpy(change_stop_1, all_time_stops_1[w5]);
                                strcpy(change_stop_2, all_time_stops_2[w5]);
                                if (*change_stop_1 == connect_stop) {
                                    change_index_1 = w5;
                                }
                                if (*change_stop_2 == connect_stop) {
                                    change_index_2 = w5;
                                }
                            }
                            if (change_index_1 != -1) {  // Print two routes according to the index value of
                                // the transfer stop
                                for (start_1_1; start_1_1 <= change_index_1; start_1_1++) {
                                    printf("%s ", stop_time_table_1[start_1_1]);
                                    printf("%s\n", all_time_stops_1[start_1_1]);
                                }
                                printf("Change at %s\n", change_stop_1);
                                for (change_index_2; change_index_2 <= end_2; change_index_2++) {
                                    printf("%s ", stop_time_table_2[change_index_2]);
                                    printf("%s\n", all_time_stops_2[change_index_2]);
                                }
                                continue;
                            }
                        } else {  // There is no connection stop between the two lines, print the first line directly
                            for (start_1_1; start_1_1 <= end_1; start_1_1++) {
                                printf("%s ", stop_time_table_1[start_1_1]);
                                printf("%s\n", all_time_stops_1[start_1_1]);
                            }
                            continue;
                        }
                    }
                    // The end stop only exists in the second line
                } else if (end_1 >= number_of_stations && end_2 < number_of_stations) {
                    char connect_stop = 0;
                    if (connect_stop != -1) {  // There is a connection stop between the two lines
                        int change_index_1 = -1;
                        int change_index_2 = -1;
                        for (int w5 = 0; w5 < end_1; w5++) {  // Find the index value of the connection stop
                            strcpy(change_stop_1, all_time_stops_1[w5]);
                            strcpy(change_stop_2, all_time_stops_2[w5]);
                            if (*change_stop_1 == connect_stop) {
                                change_index_1 = w5;
                            }
                            if (*change_stop_2 == connect_stop) {
                                change_index_2 = w5;
                            }
                        }
                        if (change_index_1 != -1) {  // Print two lines separately according to the index value
                            // of the transfer stop
                            for (start_1_1; start_1_1 <= change_index_1; start_1_1++) {
                                printf("%s ", stop_time_table_1[start_1_1]);
                                printf("%s\n", all_time_stops_1[start_1_1]);
                            }
                            printf("Change at %s\n", change_stop_1);
                            for (change_index_2; change_index_2 <= end_2; change_index_2++) {
                                printf("%s ", stop_time_table_2[change_index_2]);
                                printf("%s\n", all_time_stops_2[change_index_2]);
                            }
                            continue;
                        }
                    } else {
                        printf("No connection found.\n");
                        continue;
                    }
                } else if (end_1 < number_of_stations && end_2 >= number_of_stations) {  // The end stop is only
                    // on the first line
                    if (start_1 < end_1) {
                        for (start_1_1; start_1_1 <= end_1; start_1_1++) {  // Direct output
                            printf("%s ", stop_time_table_1[start_1_1]);
                            printf("%s\n", all_time_stops_1[start_1_1]);
                        }
                        continue;
                    }
                } else {  //No end stop found
                    printf("No connection found.\n");
                    continue;
                }
            } else if (start_2 < number_of_stations) {  // The starting stop is on the second line
                if (end_1 < number_of_stations && end_2 < number_of_stations) { // The end stop exists on both
                    // the first and second lines
                    if (strcmp(end_time_1, end_time_2) > 0) { //The second line arrives early and outputs directly
                        if (start_2 < end_2) {
                            for (start_2_2; start_2_2 <= end_2; start_2_2++) {
                                printf("%s ", stop_time_table_2[start_2_2]);
                                printf("%s\n", all_time_stops_2[start_2_2]);
                            }
                            continue;
                        }
                    } else if (strcmp(end_time_1, end_time_2) < 0) {
                        //The first line arrives early, see if there is a connection stop between the two lines
                        char connect_stop = 0;
                        if (connect_stop != -1) {  // There is a connection stop between the two lines
                            int change_index_1 = -1;
                            int change_index_2 = -1;
                            for (int w5 = 0; w5 < end_1; w5++) {  // Find the index value of the connection stop
                                strcpy(change_stop_1, all_time_stops_1[w5]);
                                strcpy(change_stop_2, all_time_stops_2[w5]);
                                if (*change_stop_1 == connect_stop) {
                                    change_index_1 = w5;
                                }
                                if (*change_stop_2 == connect_stop) {
                                    change_index_2 = w5;
                                }
                            }
                            if (change_index_1 != -1) {  // Print two lines separately according to the
                                // index value of the transfer stop
                                for (start_2_2; start_2_2 <= change_index_2; start_2_2++) {
                                    printf("%s ", stop_time_table_2[start_2_2]);
                                    printf("%s\n", all_time_stops_2[start_2_2]);
                                }
                                printf("Change at %s\n", change_stop_1);
                                for (change_index_1; change_index_1 <= end_1; change_index_1++) {
                                    printf("%s ", stop_time_table_1[change_index_1]);
                                    printf("%s\n", all_time_stops_1[change_index_1]);
                                }
                                continue;
                            }
                        } else {  // No connection stop between the two lines, directly output from the second line
                            for (start_2_2; start_2_2 <= end_2; start_2_2++) {
                                printf("%s ", stop_time_table_2[start_2_2]);
                                printf("%s\n", all_time_stops_2[start_2_2]);
                            }
                            continue;
                        }
                    }
                    // The end stop is only on the first line
                } else if (end_1 < number_of_stations && end_2 >= number_of_stations) {
                    char connect_stop = 0;
                    if (connect_stop != -1) {  // There is a connection stop between the two lines
                        int change_index_1 = -1;
                        int change_index_2 = -1;
                        for (int w5 = 0; w5 < end_1; w5++) {  // Find the index value of the connection
                            // stop of the two lines
                            strcpy(change_stop_1, all_time_stops_1[w5]);
                            strcpy(change_stop_2, all_time_stops_2[w5]);
                            if (*change_stop_1 == connect_stop) {
                                change_index_1 = w5;
                            }
                            if (*change_stop_2 == connect_stop) {
                                change_index_2 = w5;
                            }
                        }
                        if (change_index_1 != -1) {  // Output two lines separately according to
                            // the index value of the transfer stop
                            for (start_2_2; start_2_2 <= change_index_2; start_2_2++) {
                                printf("%s ", stop_time_table_2[start_2_2]);
                                printf("%s\n", all_time_stops_2[start_2_2]);
                            }
                            printf("Change at %s\n", change_stop_1);
                            for (change_index_1; change_index_1 <= end_1; change_index_1++) {
                                printf("%s ", stop_time_table_1[change_index_1]);
                                printf("%s\n", all_time_stops_1[change_index_1]);
                            }
                            continue;
                        }
                    } else {  // The two lines are not connected, directly output from the second
                        for (start_2_2; start_2_2 <= end_2; start_2_2++) {
                            printf("%s ", stop_time_table_2[start_2_2]);
                            printf("%s\n", all_time_stops_2[start_2_2]);
                        }
                        continue;
                    }
                } else if (end_1 >= number_of_stations && end_2 < number_of_stations) {  // The end stop only exists
                    // on the second line
                    if (start_2 < end_2) {
                        for (start_2_2; start_2_2 <= end_2; start_2_2++) {
                            printf("%s ", stop_time_table_2[start_2_2]);
                            printf("%s\n", all_time_stops_2[start_2_2]);
                        }
                        continue;
                    }
                } else {  // No end stop found
                    printf("No connection found.\n");
                    continue;
                }
            } else {
                printf("No connection found.\n");
                continue;
            }
        } else {  // If the input start site is ‘done’, then end use
            printf("Thank you for using goNSW.\n");
            break;
        }
        m++;
    }
}


/*
 main function, start
*/
int main(int argc,char *argv[]) {
    
    int i,j, k;
    int stopSum;
    printf("Enter the total number of stops on the network: ");
    scanf("%d", &stopSum);
    char **stops = (char**)malloc(sizeof(char*)*stopSum);  // 二维指针，获取全部站点名字
    for (i=0;i<stopSum;i++) {
         stops[i] = (char*)malloc(sizeof(char)*35);
         scanf("%s",stops[i]);
    }
    printf("Enter the number of schedules: ");
    int numbers;
    scanf("%d", &numbers);
    int **indexs = (int**)malloc(sizeof(int *)*numbers);  // 二维指针，记录一会儿每一个schedule每个值的索引
    int **times = (int**)malloc(sizeof(int *)*numbers);  // 二维指针，存放时间
    char timeStr[5];
    char nameStr[35];  
    for (i=0;i<numbers;i++) {
        printf("Enter the number of stops: ");
        int tmp;
        scanf("%d", &tmp);
        indexs[i] = (int*)malloc(sizeof(int)*stopSum);
        times[i] =  (int*)malloc(sizeof(int)*stopSum);
        for (j=0;j<tmp; j++) {
            scanf("%s", timeStr);
            scanf("%s",nameStr);
            int r = -1;  // 初始化找到站点名字的索引值
            for (k=0;k<stopSum;k++) {
                if (strcmp(stops[k], nameStr) == 0) {  // 找到输入站点在总站点里面的索引值
                    r = k + 1;
                    break;
                }
            }        
	    indexs[i][j]=r;  // 把站点名的索引值记录下来
	    times[i][j]=getIntTime(timeStr);  // 获取站点时间的int型
        }
        for (j=tmp;j<stopSum;j++) {  // 输入完一条线路的，就重新初始化一遍
            indexs[i][j] = 0;
            times[i][j] = -1;
        }
    }
    printf("\n"); 
    findWay(stops, stopSum, numbers, indexs, times);  // 寻找线路，如果找到就会直接输出

    // 程序结束时free掉所有前面所有分配的内存
    for(i=0;i<stopSum;i++) {
        free(stops[i]);
    }
    for (i=0;i<numbers;i++) {
        free(indexs[i]);
        free(times[i]);
    }
    free(indexs);
    free(times);
    free(stops);
    return 0;
}
