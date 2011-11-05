//using System;
//using System.Collections.Generic;
//using System.Windows.Forms;
//using Microsoft.VisualStudio.DebuggerVisualizers;

//namespace Bibim.Graphics
//{
//    /// <summary>
//    /// A Visualizer for ImageCookingTag.  
//    /// </summary>
//    public class ImageCookingTagDebuggerVisualizer : DialogDebuggerVisualizer
//    {
//        protected override void Show(IDialogVisualizerService windowService, IVisualizerObjectProvider objectProvider)
//        {
//            if (windowService == null)
//                throw new ArgumentNullException("windowService");
//            if (objectProvider == null)
//                throw new ArgumentNullException("objectProvider");

//            ImageCookingTag data = (ImageCookingTag)objectProvider.GetObject();

//            using (ImageViewForm displayForm = new ImageViewForm())
//            {
//                displayForm.TargetImage = data.Bitmap;
//                windowService.ShowDialog(displayForm);
//            }
//        }

//        /// <summary>
//        /// Tests the visualizer by hosting it outside of the debugger.
//        /// </summary>
//        /// <param name="objectToVisualize">The object to display in the visualizer.</param>
//        public static void TestShowVisualizer(object objectToVisualize)
//        {
//            VisualizerDevelopmentHost visualizerHost = new VisualizerDevelopmentHost(objectToVisualize, typeof(ImageCookingTagDebuggerVisualizer));
//            visualizerHost.ShowVisualizer();
//        }
//    }
//}
