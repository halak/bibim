namespace Halak.Bibim.Graphics
{
    partial class ImageViewForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ImageViewForm));
            this.toolStripMain = new System.Windows.Forms.ToolStrip();
            this.pictureBoxMain = new System.Windows.Forms.PictureBox();
            this.labelDescription = new System.Windows.Forms.Label();
            this.toolStripButtonShowDescription = new System.Windows.Forms.ToolStripButton();
            this.toolStripMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxMain)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStripMain
            // 
            this.toolStripMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButtonShowDescription});
            this.toolStripMain.Location = new System.Drawing.Point(0, 0);
            this.toolStripMain.Name = "toolStripMain";
            this.toolStripMain.Size = new System.Drawing.Size(655, 25);
            this.toolStripMain.TabIndex = 1;
            this.toolStripMain.Text = "toolStrip1";
            // 
            // pictureBoxMain
            // 
            this.pictureBoxMain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBoxMain.BackColor = System.Drawing.Color.Transparent;
            this.pictureBoxMain.Location = new System.Drawing.Point(0, 25);
            this.pictureBoxMain.Margin = new System.Windows.Forms.Padding(0);
            this.pictureBoxMain.Name = "pictureBoxMain";
            this.pictureBoxMain.Size = new System.Drawing.Size(655, 371);
            this.pictureBoxMain.TabIndex = 2;
            this.pictureBoxMain.TabStop = false;
            // 
            // labelDescription
            // 
            this.labelDescription.AutoSize = true;
            this.labelDescription.BackColor = System.Drawing.Color.Transparent;
            this.labelDescription.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelDescription.Font = new System.Drawing.Font("Malgun Gothic", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.labelDescription.Location = new System.Drawing.Point(12, 34);
            this.labelDescription.Name = "labelDescription";
            this.labelDescription.Size = new System.Drawing.Size(64, 15);
            this.labelDescription.TabIndex = 3;
            this.labelDescription.Text = "Image Info";
            // 
            // toolStripButtonShowDescription
            // 
            this.toolStripButtonShowDescription.Checked = true;
            this.toolStripButtonShowDescription.CheckOnClick = true;
            this.toolStripButtonShowDescription.CheckState = System.Windows.Forms.CheckState.Checked;
            this.toolStripButtonShowDescription.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButtonShowDescription.Image")));
            this.toolStripButtonShowDescription.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButtonShowDescription.Name = "toolStripButtonShowDescription";
            this.toolStripButtonShowDescription.Size = new System.Drawing.Size(118, 22);
            this.toolStripButtonShowDescription.Text = "show description";
            this.toolStripButtonShowDescription.CheckedChanged += new System.EventHandler(this.toolStripButtonShowDescription_CheckedChanged);
            // 
            // ImageViewForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Halak.Bibim.DesignResources.Transparent;
            this.ClientSize = new System.Drawing.Size(655, 395);
            this.Controls.Add(this.labelDescription);
            this.Controls.Add(this.pictureBoxMain);
            this.Controls.Add(this.toolStripMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ImageViewForm";
            this.ShowInTaskbar = false;
            this.Text = "ImageViewForm";
            this.toolStripMain.ResumeLayout(false);
            this.toolStripMain.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxMain)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStripMain;
        private System.Windows.Forms.PictureBox pictureBoxMain;
        private System.Windows.Forms.Label labelDescription;
        private System.Windows.Forms.ToolStripButton toolStripButtonShowDescription;

    }
}