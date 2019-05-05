
package com.QuickPushQuizAndroid.Packaging;
import android.app.NativeActivity;
import android.app.AlertDialog;

public class QuickPushQuiz extends NativeActivity {
	public void ShowMessageBox(String Message){
		new AlertDialog.Builder(this)
			.setTitle("もぎ取れ！慰謝料!")
			.setMessage(Message)
			.setPositiveButton("OK", null)
			.show();
	}
}
