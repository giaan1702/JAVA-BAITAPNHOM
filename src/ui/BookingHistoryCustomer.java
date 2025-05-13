package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;

public class BookingHistoryCustomer extends JPanel {
    private JTable scheduleTable;
    private DefaultTableModel tableModel;

    public BookingHistoryCustomer(int customerId) {
        setLayout(new BorderLayout());

        String[] columnNames = {"ID Phòng", "Ngày đặt", "Ngày trả phòng", "Thành tiền"};
        tableModel = new DefaultTableModel(columnNames, 0);

        // Dữ liệu giả lập - bạn có thể thay bằng dữ liệu từ DAO hoặc database

        scheduleTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(scheduleTable);

        JLabel titleLabel = new JLabel("Lịch sử đặt phòng", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 18));
        titleLabel.setBorder(BorderFactory.createEmptyBorder(10, 0, 10, 0));

        add(titleLabel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
    }

}
