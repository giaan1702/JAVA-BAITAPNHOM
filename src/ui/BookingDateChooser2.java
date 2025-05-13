package ui;

import javax.swing.*;
import com.toedter.calendar.JDateChooser;
import java.awt.*;
import java.util.Date;

public class BookingDateChooser2 extends JFrame {

    private JDateChooser checkInDateChooser;
    private JDateChooser checkOutDateChooser;
    private JButton nextButton;
    private int customerId;

    // Constructor nhận customerId
    public BookingDateChooser2(int customerId) {
        this.customerId = customerId;

        setTitle("Chọn ngày đặt phòng");
        setSize(350, 200);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLayout(new GridLayout(3, 2, 10, 10));

        checkInDateChooser = new JDateChooser();
        checkOutDateChooser = new JDateChooser();
        nextButton = new JButton("Tiếp tục");

        nextButton.addActionListener(e -> {
            Date checkIn = checkInDateChooser.getDate();
            Date checkOut = checkOutDateChooser.getDate();

            if (checkIn != null && checkOut != null && checkOut.after(checkIn)) {
                // Truyền customerId, checkIn, checkOut sang RoomSelection
                new RoomSelection(customerId, checkIn, checkOut, this);
                setVisible(false);
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn ngày hợp lệ!", "Lỗi", JOptionPane.WARNING_MESSAGE);
            }
        });

        add(new JLabel("Ngày nhận phòng:")); add(checkInDateChooser);
        add(new JLabel("Ngày trả phòng:")); add(checkOutDateChooser);
        add(new JLabel()); add(nextButton);

        setVisible(true);
    }
}
