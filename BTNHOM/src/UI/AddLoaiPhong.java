package UI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;

import DATA.LoaiPhong;
import DATA.Phong;
import Service.LoaiPhongService;
import Service.PhongService;
import java.util.List;
import java.awt.*;
import javax.swing.*;
public class AddLoaiPhong extends JFrame implements ActionListener {
	
    private JComboBox<String> cbLoaiPhong;
    private JTextField txtSoPhong;
    private JButton btnOK, btnQuayLai;
    private PhongService phongService;
    private LoaiPhongService loaiPhongService;
    
	public AddLoaiPhong() {
		 phongService = new PhongService();
	        loaiPhongService = new LoaiPhongService();
	        initUI();
	        loadLoaiPhong();
	}
	
	private void initUI() {
		 setTitle("Thêm Số Phòng Mới");
	        setSize(400, 200);
	        setLocationRelativeTo(null);
	        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	        setResizable(false);
	        
	        // Main panel với BorderLayout
	        JPanel mainPanel = new JPanel(new BorderLayout(10, 10));
	        mainPanel.setBorder(BorderFactory.createEmptyBorder(15, 15, 15, 15));

	        // Panel form với GridLayout
	        JPanel formPanel = new JPanel(new GridLayout(2, 2, 10, 15));
	        
	        // Thêm components
	        JLabel lblLoaiPhong = new JLabel("Loại phòng:");
	        lblLoaiPhong.setFont(new Font("Arial", Font.PLAIN, 14));
	        formPanel.add(lblLoaiPhong);
	        
	        cbLoaiPhong = new JComboBox<>();
	        cbLoaiPhong.setFont(new Font("Arial", Font.PLAIN, 14));
	        formPanel.add(cbLoaiPhong);

	        JLabel lblSoPhong = new JLabel("Số phòng:");
	        lblSoPhong.setFont(new Font("Arial", Font.PLAIN, 14));
	        formPanel.add(lblSoPhong);
	        
	        txtSoPhong = new JTextField();
	        txtSoPhong.setFont(new Font("Arial", Font.PLAIN, 14));
	        formPanel.add(txtSoPhong);

	        mainPanel.add(formPanel, BorderLayout.CENTER);

	        // Panel nút
	        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
	        btnOK = new JButton("OK");
	        btnQuayLai = new JButton("Quay lại");
	        
	        // Style nút
	        btnOK.setFont(new Font("Arial", Font.BOLD, 14));
	        btnOK.setBackground(new Color(0, 153, 76));
	        btnOK.setForeground(Color.WHITE);
	        btnOK.setPreferredSize(new Dimension(100, 35));
	        
	        btnQuayLai.setFont(new Font("Arial", Font.BOLD, 14));
	        btnQuayLai.setBackground(new Color(204, 0, 0));
	        btnQuayLai.setForeground(Color.WHITE);
	        btnQuayLai.setPreferredSize(new Dimension(100, 35));
	        
	        btnOK.addActionListener(this);
	        btnQuayLai.addActionListener(this);
	        
	        buttonPanel.add(btnOK);
	        buttonPanel.add(btnQuayLai);

	        mainPanel.add(buttonPanel, BorderLayout.SOUTH);

	        add(mainPanel);
	}
	
	private void loadLoaiPhong() {
        try {
            List<LoaiPhong> dsLoaiPhong = loaiPhongService.layTatCaLoaiPhong();
            cbLoaiPhong.removeAllItems();
            for (LoaiPhong lp : dsLoaiPhong) {
                cbLoaiPhong.addItem(lp.getTenLoai() + " - " + String.format("%,d", (int)lp.getGia()) + " VND");
            }
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Lỗi khi tải danh sách loại phòng: " + e.getMessage(), 
                "Lỗi", JOptionPane.ERROR_MESSAGE);
        }
    }
	
	@Override
	public void actionPerformed(ActionEvent e) {
		 if (e.getSource() == btnOK) {
	            handleThemPhong();
	        } else if (e.getSource() == btnQuayLai) {
	            dispose();
	        }
	}
	
	private void handleThemPhong() {
        try {
            // Lấy số phòng
            String soPhongText = txtSoPhong.getText().trim();
            if (soPhongText.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Vui lòng nhập số phòng!", 
                    "Lỗi", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            int soPhong;
            try {
                soPhong = Integer.parseInt(soPhongText);
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(this, "Số phòng phải là số nguyên!", 
                    "Lỗi", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            // Kiểm tra phòng đã tồn tại chưa
            if (phongService.findBySoPhong(soPhong) != null) {
                JOptionPane.showMessageDialog(this, "Số phòng đã tồn tại!", 
                    "Lỗi", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            // Lấy loại phòng được chọn
            int selectedIndex = cbLoaiPhong.getSelectedIndex();
            if (selectedIndex < 0) {
                JOptionPane.showMessageDialog(this, "Vui lòng chọn loại phòng!", 
                    "Lỗi", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            List<LoaiPhong> dsLoaiPhong = loaiPhongService.layTatCaLoaiPhong();
            int loaiPhongId = dsLoaiPhong.get(selectedIndex).getId();
            
            // Tạo đối tượng Phong và thêm vào CSDL
            Phong phong = new Phong(soPhong, loaiPhongId);
            if (phongService.themPhong(phong)) {
                JOptionPane.showMessageDialog(this, "Thêm phòng thành công!", 
                    "Thành công", JOptionPane.INFORMATION_MESSAGE);
                txtSoPhong.setText("");
            } else {
                JOptionPane.showMessageDialog(this, "Thêm phòng thất bại!", 
                    "Lỗi", JOptionPane.ERROR_MESSAGE);
            }
            
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "Lỗi hệ thống: " + e.getMessage(), 
                "Lỗi", JOptionPane.ERROR_MESSAGE);
            e.printStackTrace();
        }
	}
}
