import torch

class ResidualBlock(torch.nn.Module):
    def __init__(self,channel_in,channel_out,stride):
        super(ResidualBlock, self).__init__()

        self.conv1 = torch.nn.Conv2d(channel_in,channel_out,kernel_size=3,stride=stride,padding=1)
        self.bn1 = torch.nn.BatchNorm2d(channel_out)
        self.relu1 = torch.nn.ReLU()
        self.conv2 = torch.nn.Conv2d(channel_out,channel_out,kernel_size=3,stride=1,padding=1)
        self.bn2 = torch.nn.BatchNorm2d(channel_out)

        self.extra = torch.nn.Sequential(
            torch.nn.Conv2d(channel_in,channel_out,kernel_size=1,stride=stride,padding=0)
        )

    def forward(self,x):
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu1(out)
        out = self.conv2(out)
        out = self.bn2(out)

        out = self.extra(x)+out
        return out

class resnet18(torch.nn.Module):
    def __init__(self,classnum):
        super(resnet18,self).__init__()
        self.conv1 = torch.nn.Conv2d(3,16,kernel_size=3,stride=3,padding=0)
        self.bn1 = torch.nn.BatchNorm2d(16)

        self.blk1 = ResidualBlock(16,32,stride=3)
        self.blk2 = ResidualBlock(32,64,stride=3)
        self.blk3 = ResidualBlock(64,128,stride=2)
        self.blk4 = ResidualBlock(128,256,stride=2)

        self.fc = torch.nn.Linear(256*3*3,classnum)

    def forward(self,x):
        out = self.conv1(x)
        out = self.bn1(out)

        out = self.blk1(out)
        out = self.blk2(out)
        out = self.blk3(out)
        out = self.blk4(out)

        out = out.view(out.size(0),-1)
        out = self.fc(out)

        return out

def main():
    resnet = resnet18(5).cuda()
    x = torch.randn([2,3,224,224]).cuda()
    out = resnet(x)
    print(out.shape)
    #params = sum(p.numel() for p in list(net.parameters()))
    #map(lambda x: x ** 2, [1, 2, 3, 4, 5])  使用 lambda 匿名函数
    p = sum(map(lambda p: p.numel(), resnet.parameters()))#numel()函数：返回数组中元素的个数
    print('parameters size:', p)

if __name__ == '__main__':
    main()





