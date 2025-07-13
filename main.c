    // 起床準備 -> 上班途中
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
