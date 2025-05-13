package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.List;
import java.util.ArrayList;
import java.util.Date;

public class RoomSelection extends JFrame {
    private JTable roomTable;
    private JButton selectButton;
    private JButton backButton;
    private List<Room> availableRooms;
    private int customerId;

    public RoomSelection(int customerId, Date checkIn, Date checkOut, JFrame previousFrame) {
        this.customerId = customerId;

        setTitle("Chọn phòng khả dụng");
        setSize(500, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLayout(new BorderLayout());

        availableRooms = new ArrayList<>();
        availableRooms.add(new Room(23, 1, 300000)); // ID phòng là int
        availableRooms.add(new Room(24, 2, 500000));
        availableRooms.add(new Room(25, 3, 700000));

        String[] columnNames = {"Mã phòng", "Loại phòng", "Giá (VND)"};
        DefaultTableModel model = new DefaultTableModel(columnNames, 0) {
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        for (Room room : availableRooms) {
            model.addRow(new Object[]{room.id, room.type, room.price});
        }

        roomTable = new JTable(model);
        JScrollPane scrollPane = new JScrollPane(roomTable);
        add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        selectButton = new JButton("Chọn phòng");
        backButton = new JButton("Quay lại");

        selectButton.addActionListener(e -> {
            int selectedRow = roomTable.getSelectedRow();
            if (selectedRow != -1) {
                Room selectedRoom = availableRooms.get(selectedRow);
                new BookingConfirmation(customerId, checkIn, checkOut, selectedRoom, this, previousFrame);
                this.setVisible(false);
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một phòng.");
            }
        });

        backButton.addActionListener(e -> {
            previousFrame.setVisible(true);
            dispose();
        });

        buttonPanel.add(backButton);
        buttonPanel.add(selectButton);
        add(buttonPanel, BorderLayout.SOUTH);

        setVisible(true);
    }

    public static class Room {
        int id; // ID phòng thay đổi sang kiểu int
        int type;
        int price;

        public Room(int id, int type, int price) {
            this.id = id;
            this.type = type;
            this.price = price;
        }
    }
}
