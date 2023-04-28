import React from "react";
import { styled } from "@mui/material/styles";
import { AppBar, Drawer, IconButton, List, ListItemButton, ListItemIcon, ListItemText, Toolbar, Typography } from '@mui/material';
import { Menu as MenuIcon, Dashboard as DashboardIcon, Settings as SettingsIcon } from '@mui/icons-material';

const drawerWidth = 300;

const Main = styled("main")(({ theme }) => ({
  flexGrow: 1,
  padding: theme.spacing(3),
}));

const DrawerHeader = styled("div")(({ theme }) => ({
  display: "flex",
  alignItems: "center",
  justifyContent: "flex-end",
  padding: theme.spacing(0, 1),
  ...theme.mixins.toolbar,
}));

const DrawerWrapper = styled("nav")(({ theme }) => ({
  width: drawerWidth,
  flexShrink: 0,
}));

const DrawerList = styled(List)(({ theme }) => ({
  marginTop: theme.spacing(1),
}));

function Dashboard() {
  const [isDrawerOpen, setIsDrawerOpen] = React.useState(false);

  const toggleDrawer = () => {
    setIsDrawerOpen(!isDrawerOpen);
  };

  return (
    <div>
      <AppBar position="fixed">
        <Toolbar sx={{ display: "flex", justifyContent: "space-between" }}>
          <IconButton color="inherit" onClick={toggleDrawer}>
            <MenuIcon />
          </IconButton>
          <Typography variant="h6" component="div">
            Dev Scoreboard Dashboard
          </Typography>
        </Toolbar>
      </AppBar>
      <DrawerWrapper>
        <Drawer
          variant="temporary"
          anchor="left"
          open={isDrawerOpen}
          onClose={toggleDrawer}
        >
          <DrawerHeader>
            <IconButton onClick={toggleDrawer}>
              <MenuIcon />
            </IconButton>
          </DrawerHeader>
          <DrawerList>
            <ListItemButton>
              <ListItemIcon>
                <DashboardIcon />
              </ListItemIcon>
              <ListItemText primary="Stats" />
            </ListItemButton>
            <ListItemButton>
              <ListItemIcon>
                <SettingsIcon />
              </ListItemIcon>
              <ListItemText primary="Settings" />
            </ListItemButton>
          </DrawerList>
        </Drawer>
      </DrawerWrapper>
      <Main>{/* Add any dashboard components here */}</Main>
    </div>
  );
}

export default Dashboard;
