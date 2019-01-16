/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package planocartesionano;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;
import static planocartesionano.CGTemplate.CANVAS_HEIGHT;
import static planocartesionano.CGTemplate.CANVAS_WIDTH;

/**
 *
 * @author miguel
 */
  /**
    * Define inner class DrawCanvas, which is a JPanel used for custom drawing.
    */
public class DrawCanvas extends JPanel {

    /**
     * @param coordenadas the coordenadas to set
     */
    public void setCoordenadas(Coordenada[] coordenadas, int color) {
        this.repaint();
        System.out.print("Entro1");
        this.valores = true;
        this.coordenadas = coordenadas;
        this.color = color;
        this.repaint();
       
    }

    private Coordenada coordenadas[];
    private int color;
    private boolean valores;

    public DrawCanvas() {
        valores = false;
    }

    // Override paintComponent to perform your own painting
    @Override
    public void paintComponent(Graphics g) {
        
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D)g;
// paint parent's background
        setBackground(Color.WHITE);  // set background color for this JPanel

        g2d.setColor(Color.BLUE);

        g2d.drawLine(CANVAS_WIDTH / 2, 0, CANVAS_WIDTH / 2, CANVAS_HEIGHT);// EJe y
        g2d.drawLine(0, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT / 2);//Eje x
    
        // Your custom painting codes. For example,
        // Drawing primitive shapes
        
        if(color == 1)
            g2d.setColor(Color.RED);    // set the drawing color
        if(color == 2)
            g2d.setColor(Color.WHITE);
        
        if (valores) {

            for (int i = 0; i < coordenadas.length - 1; i++) {
                g2d.drawLine(coordenadas[i].getX(), coordenadas[i].getY(), coordenadas[i + 1].getX(), coordenadas[i + 1].getY());
            }

        }
        
        // Printing texts
    }
}
