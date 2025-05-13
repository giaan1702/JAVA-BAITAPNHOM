package ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddRoom extends JFrame {

    private JTextField roomIdField;
    private JComboBox<Integer> roomTypeBox;
    private JButton saveButton, cancelButton;

    private RoomManagementPanel parentPanel;

    public AddRoom(RoomManagementPanel parentPanel) {
        this.parentPanel = parentPanel;
        setTitle("Thêm phòng mới");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(300, 200);
        setLocationRelativeTo(null);
        JPanel panel = new JPanel(new GridLayout(3, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

        panel.add(new JLabel("ID phòng:"));
        roomIdField = new JTextField();
        panel.add(roomIdField);

        panel.add(new JLabel("Loại phòng:"));
        roomTypeBox = new JComboBox<>(new Integer[]{1, 2, 3, 4});
        panel.add(roomTypeBox);

        saveButton = new JButton("Lưu");
        cancelButton = new JButton("Hủy");

        saveButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String roomId = roomIdField.getText().trim();
                Integer roomType = (Integer) roomTypeBox.getSelectedItem();

                if (roomId.isEmpty()) {
                    JOptionPane.showMessageDialog(AddRoom.this, "ID phòng không được để trống.", "Lỗi", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                dispose();
            }
        });

        cancelButton.addActionListener(e -> dispose());

        panel.add(saveButton);
        panel.add(cancelButton);

        add(panel);
    }
}
