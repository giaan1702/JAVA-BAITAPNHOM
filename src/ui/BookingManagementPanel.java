package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.text.SimpleDateFormat;
import java.util.Date;

public class BookingManagementPanel extends JPanel {

    private JTable bookingTable;
    private DefaultTableModel tableModel;

    public BookingManagementPanel() {
        setLayout(new BorderLayout());

        JLabel titleLabel = new JLabel("<html><h3>Quản lý Đặt phòng</h3></html>", SwingConstants.CENTER);
        add(titleLabel, BorderLayout.NORTH);

        // === Bảng lịch đặt ===
        String[] columns = {"ID phòng", "ID khách", "Ngày đặt", "Ngày trả"};
        tableModel = new DefaultTableModel(columns, 0) {
        	public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        bookingTable = new JTable(tableModel);

        // Dữ liệu mẫu (có thể thay bằng dữ liệu thực từ DB/service)
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        tableModel.addRow(new Object[]{"23B", 1, sdf.format(new Date()), sdf.format(new Date())});
        tableModel.addRow(new Object[]{"24C", 2, "15/05/2025", "17/05/2025"});

        JScrollPane scrollPane = new JScrollPane(bookingTable);
        add(scrollPane, BorderLayout.CENTER);

        // === Nút thêm đặt phòng ===
        JButton newBookingBtn = new JButton("Thêm đặt phòng mới");
        newBookingBtn.setPreferredSize(new Dimension(200, 40));
        newBookingBtn.addActionListener(e -> {
            new BookingDateChooser(); // Form thêm đặt phòng có sử dụng calendar
        });

        JPanel bottomPanel = new JPanel();
        bottomPanel.add(newBookingBtn);
        add(bottomPanel, BorderLayout.SOUTH);
    }
}
