// 1. 定義狀態 (States) - 更新為截圖中的狀態
typedef enum {
    STATE_SLEEPING,             // 睡覺中
    STATE_GETTING_READY,        // 起床準備
    STATE_COMMUTING_TO_WORK,    // 上班途中
    STATE_WORKING,              // 工作中
    STATE_LUNCH_TIME,           // 午餐時間
    STATE_AFTERNOON_WORK,       // 下午工作
    STATE_COMMUTING_HOME,       // 下班途中
    STATE_LEISURE_TIME,         // 休閒時間
    STATE_PREPARING_FOR_SLEEP,  // 洗澡準備睡覺
    STATE_UNKNOWN               // 未知狀態，用於錯誤處理或預設值
} State;

// 2. 定義事件 (Events) - 更新為截圖中的事件
typedef enum {
    EVENT_ALARM_RINGS,          // 鬧鐘響
    EVENT_DEPARTURE_TIME,       // 出門時間到
    EVENT_ARRIVE_COMPANY,       // 到公司
    EVENT_LUNCH_TIME_ARRIVES,   // 午餐時間到
    EVENT_EATEN_ENOUGH,         // 吃飽了
    EVENT_OFF_DUTY_TIME,        // 下班時間到
    EVENT_ARRIVE_HOME,          // 到家了
    EVENT_BEDTIME,              // 睡覺時間
    EVENT_FINISHED_SHOWER,      // 洗完澡準備躺平
    EVENT_INVALID               // 無效事件，用於錯誤處理或預設值
} Event;

// 3. 定義動作函數指針 (Action Function Pointer)
// 這些函數將在狀態轉換時被呼叫
typedef void (*Action)(void);

// 4. 定義轉換結構 (Transition Structure)
// 每個轉換包含當前狀態、觸發事件、下一個狀態以及一個可選的動作函數
typedef struct {
    State current_state;    // 當前狀態
    Event event;            // 觸發此轉換的事件
    State next_state;       // 轉換後進入的新狀態
    Action action;          // 在轉換時執行的動作函數 (可為 NULL)
} Transition;

// 5. 定義所有狀態的動作函數 (Action Functions) - 更新以配合新狀態
void do_action_alarm_rings(void) {
    printf("執行動作: 鬧鐘響了，開始起床準備...\n");
}

void do_action_departure_time(void) {
    printf("執行動作: 出門時間到了，開始上班途中...\n");
}

void do_action_arrive_company(void) {
    printf("執行動作: 到公司了，開始工作...\n");
}

void do_action_lunch_time_arrives(void) {
    printf("執行動作: 午餐時間到了，準備吃飯...\n");
}

void do_action_eaten_enough(void) {
    printf("執行動作: 吃飽了，準備下午工作...\n");
}

void do_action_off_duty_time(void) {
    printf("執行動作: 下班時間到了，開始下班途中...\n");
}

void do_action_arrive_home(void) {
    printf("執行動作: 到家了，開始休閒時間...\n");
}

void do_action_bedtime(void) {
    printf("執行動作: 睡覺時間到了，準備洗澡睡覺...\n");
}

void do_action_finished_shower(void) {
    printf("執行動作: 洗完澡了，準備躺平睡覺...\n");
}

void do_no_action(void) {
    // 沒有特定動作
    printf("執行動作: 無特定動作。\n");
}

// 6. 創建轉換表 (Transition Table) - 更新為截圖中的轉換規則
static const Transition transition_table[] = {
    // 當前狀態                 事件                    下一個狀態                  動作函數
    {STATE_SLEEPING,            EVENT_ALARM_RINGS,      STATE_GETTING_READY,        do_action_alarm_rings},
    {STATE_GETTING_READY,       EVENT_DEPARTURE_TIME,   STATE_COMMUTING_TO_WORK,    do_action_departure_time},
    {STATE_COMMUTING_TO_WORK,   EVENT_ARRIVE_COMPANY,   STATE_WORKING,              do_action_arrive_company},
    {STATE_WORKING,             EVENT_LUNCH_TIME_ARRIVES,STATE_LUNCH_TIME,         do_action_lunch_time_arrives},
    {STATE_LUNCH_TIME,          EVENT_EATEN_ENOUGH,     STATE_AFTERNOON_WORK,       do_action_eaten_enough},
    {STATE_AFTERNOON_WORK,      EVENT_OFF_DUTY_TIME,    STATE_COMMUTING_HOME,       do_action_off_duty_time},
    {STATE_COMMUTING_HOME,      EVENT_ARRIVE_HOME,      STATE_LEISURE_TIME,         do_action_arrive_home},
    {STATE_LEISURE_TIME,        EVENT_BEDTIME,          STATE_PREPARING_FOR_SLEEP,  do_action_bedtime},
    {STATE_PREPARING_FOR_SLEEP, EVENT_FINISHED_SHOWER,  STATE_SLEEPING,             do_action_finished_shower},
};

void process_event(State *current_state, Event event) {
    int num_transitions = sizeof(transition_table) / sizeof(Transition);
    for (int i = 0; i < num_transitions; i++) {
        if (transition_table[i].current_state == *current_state &&
            transition_table[i].event == event) {

            printf("----------------------------------------\n");
            printf("從狀態 %d 接收到事件 %d -> ", *current_state, event);

            if (transition_table[i].action != NULL) {
                transition_table[i].action();
            } else {
                do_no_action();
            }

            *current_state = transition_table[i].next_state;
            printf("轉換到狀態 %d\n", *current_state);
            printf("----------------------------------------\n\n");
            return;
        }
    }

    printf("警告: 在狀態 %d 中接收到事件 %d，但沒有找到有效的轉換。\n\n", *current_state, event);
}

// 函數用於顯示當前狀態 - 更新以配合新狀態
void display_current_state(State state) {
    printf("當前狀態: ");
    switch (state) {
        case STATE_SLEEPING:
            printf("睡覺中 (STATE_SLEEPING)\n");
            break;
        case STATE_GETTING_READY:
            printf("起床準備 (STATE_GETTING_READY)\n");
            break;
        case STATE_COMMUTING_TO_WORK:
            printf("上班途中 (STATE_COMMUTING_TO_WORK)\n");
            break;
        case STATE_WORKING:
            printf("工作中 (STATE_WORKING)\n");
            break;
        case STATE_LUNCH_TIME:
            printf("午餐時間 (STATE_LUNCH_TIME)\n");
            break;
        case STATE_AFTERNOON_WORK:
            printf("下午工作 (STATE_AFTERNOON_WORK)\n");
            break;
        case STATE_COMMUTING_HOME:
            printf("下班途中 (STATE_COMMUTING_HOME)\n");
            break;
        case STATE_LEISURE_TIME:
            printf("休閒時間 (STATE_LEISURE_TIME)\n");
            break;
        case STATE_PREPARING_FOR_SLEEP:
            printf("洗澡準備睡覺 (STATE_PREPARING_FOR_SLEEP)\n");
            break;
        default:
            printf("未知狀態 (STATE_UNKNOWN)\n");
            break;
    }
}


// 主函數 - 示範狀態機的使用
int main() {
    State current_state = STATE_SLEEPING;

    printf("--- 狀態機演示開始 ---\n");
    display_current_state(current_state);

    // 模擬截圖中的一系列事件和轉換
    process_event(&current_state, EVENT_ALARM_RINGS);
    display_current_state(current_state);

    process_event(&current_state, EVENT_DEPARTURE_TIME);    // 起床準備 -> 上班途中
    display_current_state(current_state);

    process_event(&current_state, EVENT_ARRIVE_COMPANY);    // 上班途中 -> 工作中
    display_current_state(current_state);

    process_event(&current_state, EVENT_LUNCH_TIME_ARRIVES); // 工作中 -> 午餐時間
    display_current_state(current_state);

    process_event(&current_state, EVENT_EATEN_ENOUGH);      // 午餐時間 -> 下午工作
    display_current_state(current_state);

    process_event(&current_state, EVENT_OFF_DUTY_TIME);     // 下午工作 -> 下班途中
    display_current_state(current_state);

    process_event(&current_state, EVENT_ARRIVE_HOME);       // 下班途中 -> 休閒時間
    display_current_state(current_state);

    process_event(&current_state, EVENT_BEDTIME);           // 休閒時間 -> 洗澡準備睡覺
    display_current_state(current_state);

    process_event(&current_state, EVENT_FINISHED_SHOWER);   // 洗澡準備睡覺 -> 睡覺中
    display_current_state(current_state);

    // 嘗試無效轉換
    printf("\n--- 嘗試無效轉換 ---\n");
    process_event(&current_state, EVENT_DEPARTURE_TIME); // 當前在睡覺中，嘗試出門時間到（無效）
    display_current_state(current_state);


    printf("--- 狀態機演示結束 ---\n");

    return 0;
}
