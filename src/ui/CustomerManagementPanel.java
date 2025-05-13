package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;

public class CustomerManagementPanel extends JPanel implements ActionListener {

    private JTable userTable;
    private DefaultTableModel tableModel;
    private JButton addButton, editButton, deleteButton;

    public CustomerManagementPanel() {
        setLayout(new BorderLayout());

        JLabel panelTitle = new JLabel("<html><h3>Quản lý khách hàng</h3></html>", SwingConstants.CENTER);
        add(panelTitle, BorderLayout.NORTH);

        String[] columnNames = {"ID", "Tên đăng nhập", "Họ tên", "ID phòng"};
        tableModel = new DefaultTableModel(columnNames, 0) {
        	public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        tableModel.addRow(new Object[]{1, "guest", "Nguyễn Văn A", "23B"});
        tableModel.addRow(new Object[]{2, "guest1", "Trần Thị B", "24C"});
        tableModel.addRow(new Object[]{3, "guest2", "Lê Văn C", "25A"});

        userTable = new JTable(tableModel);
        add(new JScrollPane(userTable), BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        addButton = new JButton("Thêm người dùng");
        editButton = new JButton("Sửa người dùng");
        deleteButton = new JButton("Xóa người dùng");

        for (JButton btn : new JButton[]{addButton, editButton, deleteButton}) {
            btn.addActionListener(this);
            buttonPanel.add(btn);
        }

        add(buttonPanel, BorderLayout.SOUTH);
    }

    public void actionPerformed(ActionEvent e) {
        Object src = e.getSource();
        int selectedRow = userTable.getSelectedRow();

        if (src == addButton) {
            new AddCustomer().setVisible(true);
        } else if (src == editButton) {
            if (selectedRow != -1) {
                String userId = tableModel.getValueAt(selectedRow, 0).toString();
                // TODO: Mở form sửa người dùng
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một người dùng để sửa.", "Thông báo", JOptionPane.INFORMATION_MESSAGE);
            }
        } else if (src == deleteButton) {
            if (selectedRow != -1) {
                String userId = tableModel.getValueAt(selectedRow, 0).toString();
                int confirm = JOptionPane.showConfirmDialog(this,
                        "Bạn có chắc chắn muốn xóa người dùng ID: " + userId + "?",
                        "Xác nhận xóa", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {
                    tableModel.removeRow(selectedRow);
                }
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một người dùng để xóa.", "Thông báo", JOptionPane.INFORMATION_MESSAGE);
            }
        }
    }
}
