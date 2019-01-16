/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ServidorUDP;

/**
 *
 * @author miguel
 */
import java.io.*;
import static java.lang.Thread.sleep;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import javax.swing.SwingUtilities;
import planocartesionano.CGTemplate;
import planocartesionano.Coordenada;
//Para manejo de ByteBuffer

public class udp_servidor {

    public static void main(String args[]) throws SocketException, InterruptedException {
        DatagramSocket sock = null;
        int port = 7201;
        int numCoordenadas = 400;
        CGTemplate cgt = new CGTemplate();
        byte[] buffer = new byte[4032];
        DatagramPacket reply;
        ByteBuffer buf;
        InetAddress host;
        DatagramPacket dp;
        sock = new DatagramSocket(port);
        reply = new DatagramPacket(buffer, buffer.length);
        boolean repetido = false;
        int id = -1;
        
        int messageType;
        int requestId;
        long ip1;
        long ip2;
        int puerto;
        int operationId;
        int cantidadInfo;
        
        
        while (true) {
            try {
                
                sock.receive(reply);

                byte[] data = reply.getData();
                buf = ByteBuffer.wrap(data);

                buf.order(ByteOrder.LITTLE_ENDIAN);

                messageType = (int) buf.getInt();
                requestId = (int) buf.getInt();
                ip1 = (long) buf.getDouble();
                ip2 = (long) buf.getDouble();
                puerto = (int) buf.getInt();
                operationId = (int) buf.getInt();
                cantidadInfo = (int) buf.getShort();
                   
                repetido = false;
				
				System.out.println("MsT: "+ messageType+ "Id: "+ id + " Resquest Id: " + requestId +" puerto:" +puerto+" operationId: " +operationId);
				
				
				if(id == requestId)	
					repetido = true;
                
                if(repetido)
                {
                    System.out.print("Repetido\n");  
					host = reply.getAddress();
					dp = new DatagramPacket(buf.array(), buf.limit(), host, reply.getPort());
					sock.send(dp);
					System.out.print("Enviado\n"); 
	            }else if(id > requestId + 5){
					
				}
				else {
                    id = requestId;
                    Coordenada coordenadas[] = new Coordenada[numCoordenadas];
                    for (int i = 0; i < numCoordenadas; i++) 
                        coordenadas[i] = new Coordenada((int) buf.getShort(), (int) buf.getShort());
                    
                    System.out.print("No repetido\n");
                    cgt.redibujar(coordenadas, operationId);// Let the constructor do the job
					host = reply.getAddress();
					dp = new DatagramPacket(buf.array(), buf.limit(), host, reply.getPort());
					sock.send(dp);
					System.out.print("Enviado\n"); 
                }
				
            } catch (IOException e) {
                System.err.println("IOException " + e);
            }
        }

    }
}
