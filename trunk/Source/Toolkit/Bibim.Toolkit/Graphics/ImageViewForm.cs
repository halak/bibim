using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using GDIImage = System.Drawing.Image;

namespace Bibim.Graphics
{
    public partial class ImageViewForm : Form
    {
        private GDIImage targetImage;
        private StringBuilder descriptionBuilder;

        public GDIImage TargetImage
        {
            get { return targetImage; }
            set
            {
                if (targetImage != value)
                {
                    targetImage = value;
                    pictureBoxMain.Image = targetImage;

                    descriptionBuilder.Clear();
                    descriptionBuilder.AppendLine(string.Format("Width: {0}", targetImage.Width));
                    descriptionBuilder.AppendLine(string.Format("Height: {0}", targetImage.Height));
                    labelDescription.Text = descriptionBuilder.ToString();

                    ClientSize = new Size(targetImage.Width, targetImage.Height);
                }
            }
        }

        public ImageViewForm()
        {
            InitializeComponent();
            descriptionBuilder = new StringBuilder();
        }
        
        private void toolStripButtonShowDescription_CheckedChanged(object sender, EventArgs e)
        {
            labelDescription.Visible = toolStripButtonShowDescription.Checked;
        }
    }
}
