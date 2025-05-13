package ui;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RoomManagementPanel extends JPanel implements ActionListener {

    private JTable roomTable;
    private DefaultTableModel tableModel;
    private JButton addButton;
    private JButton editButton; 
    private JButton deleteButton;
    private JButton scheduleButton;
    private JPanel buttonPanel;

    public RoomManagementPanel() {
        setLayout(new BorderLayout());

        JLabel panelTitle = new JLabel("<html><h3>Quản lý phòng</h3></html>", SwingConstants.CENTER);
        add(panelTitle, BorderLayout.NORTH);

        String[] columnNames = {"ID", "Loại phòng"};
        tableModel = new DefaultTableModel(columnNames, 0) {
        	public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        // Dữ liệu mẫu
        tableModel.addRow(new Object[]{"23B", 4});
        tableModel.addRow(new Object[]{"24C", 1});
        tableModel.addRow(new Object[]{"25A", 3});

        roomTable = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(roomTable);
        add(scrollPane, BorderLayout.CENTER);

        buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        addButton = new JButton("Thêm phòng");
        editButton = new JButton("Sửa phòng");
        deleteButton = new JButton("Xóa phòng");
        scheduleButton = new JButton("Lịch đặt phòng");

        buttonPanel.add(addButton);
        buttonPanel.add(editButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(scheduleButton);
        add(buttonPanel, BorderLayout.SOUTH);

        addButton.addActionListener(this);
        editButton.addActionListener(this);
        deleteButton.addActionListener(this);
        scheduleButton.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
    	if (e.getSource() == addButton) {
    	    new AddRoom(this).setVisible(true);
    	} else if (e.getSource() == editButton) {
            int selectedRow = roomTable.getSelectedRow();
            if (selectedRow != -1) {
                String roomId = tableModel.getValueAt(selectedRow, 0).toString();
                // TODO: Mở form sửa
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một phòng để sửa.", "Thông báo", JOptionPane.INFORMATION_MESSAGE);
            }
        } else if (e.getSource() == deleteButton) {
            int selectedRow = roomTable.getSelectedRow();
            if (selectedRow != -1) {
                String roomId = tableModel.getValueAt(selectedRow, 0).toString();
                int confirm = JOptionPane.showConfirmDialog(this, "Bạn có chắc chắn muốn xóa phòng ID: " + roomId + "?", "Xác nhận xóa", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {
                    tableModel.removeRow(selectedRow);
                }
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một phòng để xóa.", "Thông báo", JOptionPane.INFORMATION_MESSAGE);
            }
        } else if (e.getSource() == scheduleButton) {
            int selectedRow = roomTable.getSelectedRow();
            if (selectedRow != -1) {
                String roomId = tableModel.getValueAt(selectedRow, 0).toString();
                new RoomSchedule(roomId).setVisible(true);
            } else {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn một phòng để xem lịch đặt.", "Thông báo", JOptionPane.INFORMATION_MESSAGE);
            }
        }
    }
}
