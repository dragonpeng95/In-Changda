import os,glob
from torch.utils.data import Dataset
import random
import csv
import torchvision
from PIL import Image
import torch
class Pokeman(Dataset):
    def __init__(self,root,resize,model):
        super(Pokeman, self).__init__()

        self.root = root
        self.resize = resize

        self.item = {}
        for name in sorted(os.listdir(os.path.join(root))):#讲root路径下的文件以列表返回
            if not os.path.isdir(os.path.join(root,name)):#如果不是目录继续执行for语句
                continue
            self.item[name] = len(self.item.keys())
        print(self.item)

        self.images,self.labels = self.load_csv("images_db.csv")

        if model == "train":#60%做训练集
            self.images = self.images[:int(0.6*len(self.images))]
            self.labels = self.labels[:int(0.6*len(self.labels))]

        elif model == "val":#20%做验证集
            self.images = self.images[int(0.6*len(self.images)):int(0.8*len(self.images))]
            self.labels = self.labels[int(0.6*len(self.labels)):int(0.8*len(self.labels))]

        else:#20%做测试集
            self.images = self.images[int(0.8*len(self.images)):]
            self.labels = self.labels[int(0.8*len(self.labels)):]

    def load_csv(self,filename):
        if not os.path.exists(os.path.join(self.root,filename)):
            images = []#1167 pokemandata\\bulbasaur\\00000006.jpg
            for name in self.item.keys():#将所有的jpg，png，jpeg格式的文件全部放进images里面
                images += glob.glob(os.path.join(self.root,name,"*.jpg"))#.append()是直接操作函数不能赋值，+需要赋值给新的变量
                images += glob.glob(os.path.join(self.root,name,"*.png"))
                images += glob.glob(os.path.join(self.root,name,"*.jpeg"))
            print(len(images),images)

            random.shuffle(images)
            with open(os.path.join(self.root,filename),"w",newline='') as f:
                writer = csv.writer(f)
                for image in images:
                    name = image.split(os.sep)[-2]
                    label = self.item[name]
                    writer.writerow([image,label])
                print("writen into csv file",filename)

        images = []
        labels = []
        with open(os.path.join(self.root,filename)) as f:
            reader = csv.reader(f)
            for row in reader:
                image,label = row
                images.append(image)
                labels.append(label)
        assert len(images) == len(labels)
        return images,labels

    def __len__(self):
        return len(self.images)

    def denormalization(self,x_hat):
        mean = [0.485, 0.456, 0.406]
        std = [0.229, 0.224, 0.225]
        #前面normalization压缩数据使得图像变质，现在使数据还原
        #x_hat = (x - mean)/std
        #mean.shape=[3],std.shape=[3]
        #x.shape=[c,h,w]
        mean = torch.tensor(mean).unsqueeze(-1).unsqueeze(-1)#mean.shape=[3]=>[3,1,1]
        std = torch.tensor(std).unsqueeze(-1).unsqueeze(-1)#std.shape=[3]=>[3,1,1]
        x = x_hat*std+mean
        return x

    def __getitem__(self,idx):
        img,label = self.images[idx],self.labels[idx]
        transform = torchvision.transforms.Compose([
            lambda x:Image.open(x).convert("RGB"),
            torchvision.transforms.Resize((int(1.25*self.resize),int(1.25*self.resize))),#比我们想要的大一点，然后去裁剪（增强数据）
            torchvision.transforms.RandomRotation(15),#旋转15°之后会出现黑色填充的底
            torchvision.transforms.CenterCrop((self.resize,self.resize)),#以中心裁剪就不会出现黑底
            torchvision.transforms.ToTensor(),
            torchvision.transforms.Normalize(mean=[0.485,0.456,0.406],
                                             std=[0.229,0.224,0.225])#将数据缩放至-1，1就会出现所有像素值下降
        ])
        img = transform(img)
        label = torch.tensor(int(label))

        return img,label

def main():
    import visdom
    import time

    viz = visdom.Visdom()
    pokeman = Pokeman("pokemandata",64,"train")
    # pokeman.load_csv("Images.csv")
    pokeman_db = iter(pokeman)
    x,y= next(pokeman_db)

    print(x.shape,y.shape,y)
    viz.image(pokeman.denormalization(x),win="sample_x",opts=dict(title="sample_x"))
    dataloader = torch.utils.data.DataLoader(pokeman,batch_size=32,shuffle=True)

    for x,y in dataloader:
        viz.text(str(y.numpy()),win="label",opts=dict(title="label"))
        viz.images(pokeman.denormalization(x),win="batch",nrow=8,opts=dict(title="batch-y"))

        time.sleep(5)

if __name__ == '__main__':
    main()

