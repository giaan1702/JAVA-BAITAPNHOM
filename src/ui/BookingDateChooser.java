package ui;

import javax.swing.*;
import com.toedter.calendar.JDateChooser;
import java.awt.*;
import java.util.Date;

public class BookingDateChooser extends JFrame {

    private JDateChooser checkInDateChooser;
    private JDateChooser checkOutDateChooser;
    private JButton nextButton;
    private JComboBox<String> customerCombo;

    public BookingDateChooser() {
        setTitle("Chọn ngày đặt phòng");
        setSize(350, 250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLayout(new GridLayout(4, 2, 10, 10));

        // Chọn khách hàng
        customerCombo = new JComboBox<>(new String[] {
                "1 - Nguyễn Văn A",
                "2 - Trần Thị B",
                "3 - Lê Văn C"
        });

        checkInDateChooser = new JDateChooser();
        checkOutDateChooser = new JDateChooser();
        nextButton = new JButton("Tiếp tục");

        nextButton.addActionListener(e -> {
            Date checkIn = checkInDateChooser.getDate();
            Date checkOut = checkOutDateChooser.getDate();

            // Lấy ID khách hàng từ item đã chọn trong customerCombo
            String selectedCustomer = (String) customerCombo.getSelectedItem();
            int customerId = Integer.parseInt(selectedCustomer.split(" - ")[0]); // Lấy phần trước dấu "-" làm customerId

            if (checkIn != null && checkOut != null && checkOut.after(checkIn)) {
                // Chuyển customerId, checkIn và checkOut sang RoomSelection
                new RoomSelection(customerId, checkIn, checkOut, this);
                setVisible(false);
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn ngày hợp lệ!", "Lỗi", JOptionPane.WARNING_MESSAGE);
            }
        });

        add(new JLabel("Khách hàng:")); add(customerCombo);
        add(new JLabel("Ngày nhận phòng:")); add(checkInDateChooser);
        add(new JLabel("Ngày trả phòng:")); add(checkOutDateChooser);
        add(new JLabel()); add(nextButton);

        setVisible(true);
    }
}
