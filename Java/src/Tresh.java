import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;
import java.util.TimerTask;
import java.lang.Object;
import   java.nio.file.FileSystems;
import java.nio.file.FileSystem;

public class Tresh extends JFrame{
    FileSystem fs  = FileSystems.getDefault();
    private Object row[][] = {
            {fs.getSeparator(), 2, 3},
            {"cs", "2", "4"}
    };
    private Object column[] = {fs.getSeparator(), "fdg", "dfg"};
    private  JTable table = new JTable(row, column);
    private JPanel panel = new JPanel(new GridLayout(1, 1, 1, 1));
    public TimerLabel tl = new TimerLabel();
    public Tresh(){
        final JFrame f = new JFrame();
        final JPanel contentPane = new JPanel();
        contentPane.add(new JLabel("Запустить секундомер?", JLabel.CENTER));
        contentPane.add(table);
        contentPane.add(new JButton(new AbstractAction("Запустить"){
            public void actionPerformed(ActionEvent e) {
                setContentPane(new BPanel());
                setSize(500, 340);
                Container container = getContentPane();
                // setLocationRelativeTo(null);             -      окно по центру экрана

                JButton button1 = new JButton("Stop");
                panel.add(button1);
                ActionListener actionListener = new TestActionListener();
                button1.addActionListener(actionListener);
                JButton button = new JButton("Запустить с начала");
                panel.add(button);
                ActionListener actionListene = new Test();
                button.addActionListener(actionListene);
                setResizable(false);// окно не меняет размер
                panel.setBackground(Color.BLACK);
                container.add(panel);
                panel.add(tl);
                panel.setAlignmentX(JLabel.RIGHT_ALIGNMENT);
                Font font = new Font("Verdana", Font.PLAIN, 32);
                tl.setFont(font);
                tl.setForeground(Color.WHITE);
                f.setVisible(false);
                setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            }
        }));
        contentPane.add(new JButton(new AbstractAction("Выход"){
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        }));

        f.setContentPane(contentPane);
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        SwingUtilities.invokeLater(new Runnable(){
            public void run(){
                f.pack();
                f.show();
            }
        });
    }
    class TimerLabel extends JLabel{
        public java.util.Timer timer = new java.util.Timer();
        public TimerLabel() {
            timer.scheduleAtFixedRate(timerTask, 0, 1000);
        }
        public TimerTask timerTask = new TimerTask(){
            private volatile int time = -1;
            private Runnable refresher = new Runnable(){
                public void run(){
                    int t = time;
                    DecimalFormat decimalFormat = new DecimalFormat("00"); // задаем формат вывода секундомера
                    TimerLabel.this.setText(decimalFormat.format(t / 60) + ":" + decimalFormat.format(t % 60));
                }
            };
            public void run(){
                time++;
                SwingUtilities.invokeLater(refresher);
            }

        };
        public void StopTimer() {
            timer.cancel();
        }
    }
    public static void main(String[] args) throws InterruptedException{
        JFrame app = new Tresh();
        app.setVisible(true);
    }
    public class TestActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            tl.StopTimer();
        }
    }
    public class Test implements ActionListener{
        public void actionPerformed(ActionEvent e){
            JFrame app = new Tresh();
            app.setVisible(true);
        }
    }
}

class BPanel extends JPanel{
    public void paintComponent(Graphics g){
        Image im = null;
//        try {
//            im = ImageIO.read(new File("q.jpg"));
//        }
//        catch (IOException e)
//        g.drawImage(im, 0, 0, null);
    }
}