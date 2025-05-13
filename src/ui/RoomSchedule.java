package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;

public class RoomSchedule extends JFrame {
    private JTable scheduleTable;
    private DefaultTableModel tableModel;

    public RoomSchedule(String roomId) {
        setTitle("Lịch đặt phòng - Phòng " + roomId);
        setSize(500, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        String[] columnNames = {"ID Phòng", "ID Khách hàng", "Ngày đặt", "Ngày trả phòng"};
        tableModel = new DefaultTableModel(columnNames, 0);

        // Dữ liệu giả lập - bạn có thể thay thế bằng dữ liệu thật từ DAO/service
        tableModel.addRow(new Object[]{roomId, "KH001", "2025-05-10", "2025-05-12"});
        tableModel.addRow(new Object[]{roomId, "KH002", "2025-05-15", "2025-05-18"});

        scheduleTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(scheduleTable);
        add(scrollPane, BorderLayout.CENTER);
    }
}
