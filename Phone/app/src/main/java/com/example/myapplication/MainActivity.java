package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    TextView textView;
    Handler handler = new Handler();
    EditText editText;
    ImageView imageView;
    ImageView imageView2;
    ImageView imageView3;
    Socket socket;
    TTS tts;
    TextView textView2;
    TextView textView3;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView)findViewById(R.id.textView);
        textView2 = (TextView)findViewById(R.id.textView2);
        textView3 = (TextView)findViewById(R.id.textView3);
        Button button = (Button)findViewById(R.id.button);
        editText = (EditText)findViewById(R.id.gasNumber);
        imageView = (ImageView)findViewById(R.id.imageView);
        imageView2 = (ImageView)findViewById(R.id.imageView3);
        imageView3 = (ImageView)findViewById(R.id.imageView4);
        Button button2 = (Button)findViewById(R.id.send);
        tts = new TTS(getApplicationContext());


        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                textView.setText("받은데이터: dasdasd");
                textView.setVisibility(View.INVISIBLE);
                editText.setVisibility(View.INVISIBLE);
                button.setVisibility(View.INVISIBLE);
                ClientThread thread = new ClientThread();
                thread.start();

            }
        });
        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                button2.setVisibility(View.INVISIBLE);
                SendThread thread = new SendThread();
                thread.start();
            }
        });
    }

    class ClientThread extends Thread{
        @Override
        public void run() {
            String host = "192.168.0.106"; //집의 컴으로 서버를 구현하였습니다.
            //int port = 5005;
            try {
                socket = new Socket(host, Integer.parseInt(editText.getText().toString()));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
    class SendThread extends Thread{
        @Override
        public void run() {
            try {
                ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
                outputStream.writeObject("0");//null
                outputStream.flush();
                Log.d("Client", "보냄");

                ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());
                final Object input = inputStream.readObject();//받기
                Log.d("client","받은데이터"+ input);

                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        //textView.setText("받은데이터: "+ input);
                        if (input.equals("1")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction1);
                            tts.startTTS("화재발생입니다. 왼쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("5")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction2);
                            tts.startTTS("화재발생입니다. 왼쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("2")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction3);
                            tts.startTTS("화재발생입니다. 오른쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("6")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction4);
                            tts.startTTS("화재발생입니다. 오른쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("3")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction5);
                            tts.startTTS("화재발생입니다. 오른쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("7")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction6);
                            tts.startTTS("화재발생입니다. 왼쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("4")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction7);
                            tts.startTTS("화재발생입니다. 왼쪽 비상구로 대피해주세요.");
                        }
                        else if (input.equals("8")){
                            textView2.setVisibility(View.VISIBLE);
                            textView3.setVisibility(View.VISIBLE);
                            imageView2.setVisibility(View.VISIBLE);
                            imageView3.setVisibility(View.VISIBLE);
                            imageView.setVisibility(View.VISIBLE);
                            imageView.setImageResource(R.drawable.direction8);
                            tts.startTTS("화재발생입니다. 오른쪽 비상구로 대피해주세요.");
                        }
                        else {
                            
                            imageView.setVisibility(View.INVISIBLE);
                        }
                    }
                });



            } catch (EOFException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}