package UI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.*;
import javax.swing.*;
import javax.swing.JFrame;

public class StaffDashboard extends JFrame implements ActionListener {
	private int StaffID;
    private JPanel navPanel;
    private JButton bookRoomButton;
  
    private JButton viewCustomerButton;
    private JButton paymentButton;
    private JButton logoutButton;
    private JPanel footerPanel;
    private JPanel mainPanel;
    private CardLayout cardLayout;

    // Panels
    private JPanel bookRoomPanel;
   
    private JPanel viewCustomerJPanel;
    private JPanel paymentPanel;
	
	public StaffDashboard() {
		setTitle("Hệ thống Quản lý Khách sạn - Trang Nhân Viên");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        cardLayout = new CardLayout();
        mainPanel = new JPanel(cardLayout);

        // Khởi tạo các panel (có thể thay bằng panel thực)
        bookRoomPanel = new JPanel();
       
        viewCustomerJPanel = new JPanel();
        paymentPanel = new JPanel();

        // Đăng ký các panel vào mainPanel
        mainPanel.add(bookRoomPanel, "bookRoom");
        
        mainPanel.add(viewCustomerJPanel, "bookingHistory");
        mainPanel.add(paymentPanel, "payment");

        // Tạo các nút
        bookRoomButton = new JButton("🛏 Đặt phòng");
       
        viewCustomerButton = new JButton("📅 Danh sách khách hàng");
        paymentButton = new JButton("💳 Thanh toán");
        logoutButton = new JButton("Đăng xuất");

        // Căn chỉnh nút
        Dimension buttonSize = new Dimension(200, 40);
        JButton[] buttons = {bookRoomButton, viewCustomerButton, paymentButton};
        for (JButton btn : buttons) {
            btn.setMaximumSize(buttonSize);
            btn.setAlignmentX(Component.CENTER_ALIGNMENT);
        }

        // Panel menu bên trái
        navPanel = new JPanel();
        navPanel.setLayout(new BoxLayout(navPanel, BoxLayout.Y_AXIS));
        navPanel.add(Box.createVerticalGlue());
        navPanel.add(bookRoomButton);
        navPanel.add(Box.createRigidArea(new Dimension(5, 10)));
       
      
        navPanel.add(viewCustomerButton);
        navPanel.add(Box.createRigidArea(new Dimension(5, 10)));
        navPanel.add(paymentButton);
        navPanel.add(Box.createVerticalGlue());

        add(navPanel, BorderLayout.WEST);

        // Footer với nút Đăng xuất
        footerPanel = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        footerPanel.add(logoutButton);
        add(footerPanel, BorderLayout.SOUTH);

        // Gắn ActionListener
        bookRoomButton.addActionListener(this);
      
        viewCustomerButton.addActionListener(this);
        paymentButton.addActionListener(this);
        logoutButton.addActionListener(this);

        add(mainPanel, BorderLayout.CENTER);

        JLabel welcomeLabel = new JLabel("Chào mừng, Nhân Viên!", SwingConstants.CENTER);
        mainPanel.add(welcomeLabel, "home");
        cardLayout.show(mainPanel, "home");

        setVisible(true);
    }
	
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == bookRoomButton) {
           new Booking1().setVisible(true);
       
        } else if (e.getSource() == viewCustomerButton) {
            new ViewCustomer().setVisible(true);
        } else if (e.getSource() == paymentButton) {
            new Payment().setVisible(true);
        } else if (e.getSource() == logoutButton) {
            dispose();
            new Login().setVisible(true);
        }
	}
	

}
