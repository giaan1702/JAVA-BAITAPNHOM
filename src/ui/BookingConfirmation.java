package ui;

import javax.swing.*;
import java.awt.*;
import java.util.Date;

public class BookingConfirmation extends JFrame {
    private JLabel roomLabel, priceLabel, customerLabel, customerIDLabel ;
    private JButton confirmButton, backButton;

    private Date checkIn;
    private Date checkOut;
    private RoomSelection.Room selectedRoom;
    private JFrame previousFrame;
    private int customerId;  // customerId là kiểu int

    // Constructor nhận customerId kiểu int
    public BookingConfirmation(int customerId, Date checkIn, Date checkOut, RoomSelection.Room room, JFrame roomSelectFrame, JFrame previousFrame) {
        this.customerId = customerId;  // Gán customerId kiểu int
        this.checkIn = checkIn;
        this.checkOut = checkOut;
        this.selectedRoom = room;
        this.previousFrame = previousFrame;

        setTitle("Xác nhận đặt phòng");
        setSize(400, 250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLayout(new GridLayout(6, 1, 10, 10));

        // Hiển thị thông tin khách hàng (customerId)
        customerLabel = new JLabel("Khách hàng ID: ");
        customerIDLabel = new JLabel(String.valueOf(customerId));
        // Tính toán giá
        long days = (checkOut.getTime() - checkIn.getTime()) / (1000 * 60 * 60 * 24);
        if (days == 0) days = 1;
        int totalPrice = (int) (days * selectedRoom.price);

        roomLabel = new JLabel("Phòng ID: " + selectedRoom.id + " (Loại " + selectedRoom.type + ")");
        priceLabel = new JLabel("Thành tiền: " + totalPrice + " VND");

        // Xác nhận đặt phòng
        confirmButton = new JButton("Xác nhận");
        confirmButton.addActionListener(e -> {
            JOptionPane.showMessageDialog(this,
                    "Đặt phòng thành công:\nKhách hàng ID: " + customerId +
                            "\nPhòng: " + selectedRoom.id +
                            "\nTừ: " + checkIn +
                            "\nĐến: " + checkOut +
                            "\nThành tiền: " + totalPrice + " VND");

            roomSelectFrame.dispose();
            previousFrame.dispose();
            dispose();
        });

        // Quay lại
        backButton = new JButton("Quay lại");
        backButton.addActionListener(e -> {
            roomSelectFrame.setVisible(true);
            dispose();
        });

        // Thêm các thành phần vào giao diện
        add(new JLabel("Phòng:"));
        add(roomLabel);
        add(customerLabel);  // Hiển thị khách hàng ID
        add(customerIDLabel);
        add(new JLabel("Thành tiền:"));
        add(priceLabel);
        add(backButton);
        add(confirmButton);

        setVisible(true);
    }
}
