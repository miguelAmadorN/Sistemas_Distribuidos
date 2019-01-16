/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package planocartesionano;

/**
 *
 * @author miguel
 */
import java.awt.*;
import java.awt.event.*; // Using AWT event classes and listener interfaces
import javax.swing.*;    // Using Swing's components and containers
 
/** Custom Drawing Code Template */
// A Swing application extends javax.swing.JFrame
public class CGTemplate extends JFrame {
    // Define constants

    public static final int CANVAS_WIDTH = 800;
    public static final int CANVAS_HEIGHT = 600;

    // Declare an instance of the drawing canvas,
    // which is an inner class called DrawCanvas extending javax.swing.JPanel.
    private DrawCanvas canvas;
    private Container cp;

    private void inicializar_canvas() {
        canvas = new DrawCanvas();    // Construct the drawing canvas
        canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));
        cp.add(canvas);
        
        
    }

    public void redibujar( Coordenada coordenadas[], int color )
    {
        canvas.setCoordenadas(coordenadas, color);
    }
    // Constructor to set up the GUI components and event handlers
    public CGTemplate() {
             
        // Set the Drawing JPanel as the JFrame's content-pane
        cp = getContentPane();
        this.inicializar_canvas();
        // or "setContentPane(canvas);"
        setDefaultCloseOperation(EXIT_ON_CLOSE);   // Handle the CLOSE button
        pack();              // Either pack() the components; or setSize()
        setTitle("SERIES DE FOURIER");  // "super" JFrame sets the title
        setLocationRelativeTo(null);
        setVisible(true);    // "super" JFrame show
        
    }


}
