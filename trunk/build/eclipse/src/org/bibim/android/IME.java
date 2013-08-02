package org.bibim.android;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.text.InputType;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

public class IME {
	public static class DialogParams
	{
		private Context context;
		private int id;
		private String text;
		private String title;
		private String description;
		private int maxLength;
		
		public DialogParams(
				Context context,
				int id,
				String text,
				String title,
				String description,
				int maxLength) {
			this.context = context;
			this.id = id;
			this.text = text;
			this.title = title;
			this.description = description;
			this.maxLength = maxLength;
		}
		
		public Context getContext() {
			return context;
		}
		
		public int getId() {
			return id;
		}
		
		public String getText() {
			return text;
		}
		
		public String getTitle() {
			return title;
		}
		
		public String getDescription() {
			return description;			
		}
		
		public int getMaxLength() {
			return maxLength;
			
		}
	}
	
	public static void showPlainDialog(DialogParams params) {
		final int it = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_NORMAL;
		showDialog(params, it);
	}
	
	public static void showNumberDialog(DialogParams params) {
		final int it = InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED;
		showDialog(params, it);
	}
	
	public static void showPasswordDialog(DialogParams params) {
		final int it = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_PASSWORD;
		showDialog(params, it);
	}
	
	public static void showEmailDialog(DialogParams params) {
		final int it = InputType.TYPE_CLASS_TEXT | InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS;
		showDialog(params, it);
	}
	
	private static void showDialog(DialogParams params, int inputType) {
		final Context context = params.getContext();
		final LinearLayout dialogContent = new LinearLayout(context);
		final TextView descriptionView = new TextView(context);
		final EditText editText = new EditText(context);
		
		descriptionView.setText(params.getDescription());
		editText.setInputType(inputType);
		editText.setText(params.getText());
		editText.setSelectAllOnFocus(true);
		
		final int MATCH_PARENT = ViewGroup.LayoutParams.MATCH_PARENT;
		final int WRAP_CONTENT = ViewGroup.LayoutParams.WRAP_CONTENT;
		LinearLayout.LayoutParams childLayout =
				new LinearLayout.LayoutParams(MATCH_PARENT, WRAP_CONTENT);
		childLayout.setMargins(20, 10, 20, 10);
		
		dialogContent.setOrientation(LinearLayout.VERTICAL);
		dialogContent.addView(descriptionView, childLayout);
		dialogContent.addView(editText, childLayout);
		
		final int id = params.getId();
		OnClickListener listener = new OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, final int which) {
				BaseActivity app = (BaseActivity)context;
				
				app.getSurfaceView().queueEvent(new Runnable() {
					@Override
					public void run() {
						if (which == DialogInterface.BUTTON_POSITIVE)
							JNI.handleIMESubmit(id, editText.getText().toString());
						else
							JNI.handleIMECancel(id);
					}
				});
				
				dialog.dismiss();
			}
		};
		
		new AlertDialog.Builder(context)
			.setView(dialogContent)
			.setTitle(params.getTitle())
			.setIcon(android.R.drawable.ic_dialog_alert)
			.setPositiveButton(android.R.string.ok, listener)
			.setNegativeButton(android.R.string.cancel, listener)
			.setCancelable(true)
			.show();
		
		//final InputMethodManager imm = (InputMethodManager) context.getSystemService(Context.INPUT_METHOD_SERVICE);
		//editText.requestFocus();
		//imm.showSoftInput(editText, 0);
	}
	
	private IME() {
	}
}
