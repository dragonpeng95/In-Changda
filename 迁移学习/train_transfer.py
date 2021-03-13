import torch
#from resnet18 import resnet18
from torchvision.models import resnet18
from pokeman import Pokeman
import visdom
from utils import Flatten
device = torch.device("cuda")
torch.manual_seed(1234)
viz = visdom.Visdom()
def main():
    train_db = Pokeman("pokemandata",224,"train")
    val_db = Pokeman("pokemandata",224,"val")
    test_db = Pokeman("pokemandata",224,"test")

    train_loader = torch.utils.data.DataLoader(train_db,batch_size=32,shuffle=True,num_workers=4)
    val_loader = torch.utils.data.DataLoader(val_db,batch_size=32,shuffle=False,num_workers=2)
    test_loader = torch.utils.data.DataLoader(test_db,batch_size=32,shuffle=False,num_workers=2)

    #model = resnet18(5).to(device)
    model_trained = resnet18(pretrained=True)#If True, returns a model pre-trained on ImageNet
    model = torch.nn.Sequential(
        *list(model_trained.children())[:-1],
        Flatten(),
        torch.nn.Linear(512,5),
    ).to(device)
    optimizer = torch.optim.Adam(model.parameters(),lr=1e-3)
    criteon = torch.nn.CrossEntropyLoss().to(device)
    global_step = 0
    best_accuracy = 0
    best_epoch = 0
    viz.line([0],[-1],win="loss",opts=dict(title="loss"))
    viz.line([0],[-1],win="val_accuracy",opts=dict(title="val_accuracy"))
    for epoch in range(10):
        for idx,(x,y) in enumerate(train_loader):
            x,y = x.to(device),y.to(device)
            logits = model(x)
            loss = criteon(logits,y)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            viz.line([loss.item()],[global_step],win="loss",update="append")
            global_step += 1

        correct = 0
        # val_loss = 0
        for x,y in val_loader:
            x,y = x.to(device),y.to(device)
            with torch.no_grad():
                logits = model(x)
                # loss = criteon(logits,y)
                # val_loss += loss.item()
                y_hat = logits.argmax(dim=1)
            correct += y_hat.eq(y).float().sum().item()
        val_accurancy = correct/len(val_loader.dataset)

        if val_accurancy>best_accuracy:
            best_accuracy = val_accurancy
            best_epoch = epoch

            torch.save(model.state_dict(),"best.mdl")
        viz.line([val_accurancy],[global_step],win="val_accuracy",update="append")

    print("best accuracy:",best_accuracy,"best epoch:",best_epoch)

    model.load_state_dict(torch.load("best.mdl"))
    print("load from ckpt!")

    test_correct = 0
    for x,y in test_loader:
        x,y = x.to(device),y.to(device)
        with torch.no_grad():
            logits = model(x)
            y_hat = logits.argmax(dim=1)
        test_correct += y_hat.eq(y).float().sum().item()
    test_accurancy = test_correct/len(test_loader.dataset)

    print("test_accuracy:",test_accurancy)

if __name__ == '__main__':
    main()