import {
  Box,
  Button,
  TextField,
  InputLabel,
  Select,
  MenuItem,
  FormControl,
  FormGroup,
  FormControlLabel,
  Checkbox,
  Typography,
  FormLabel,
} from "@mui/material";
import { Formik } from "formik";
import * as yup from "yup";
import useMediaQuery from "@mui/material/useMediaQuery";
import Header from "../../components/Header";

const Form = () => {
  const isNonMobile = useMediaQuery("(min-width:600px)");

  const handleFormSubmit = (values) => {
    console.log(values);
  };

  return (
    <Box m="20px">
      <Header title="MODIFY REWARD SETTINGS" />

      <Formik
        onSubmit={handleFormSubmit}
        initialValues={initialValues}
        validationSchema={checkoutSchema}
      >
        {({
          values,
          errors,
          touched,
          handleBlur,
          handleChange,
          handleSubmit,
        }) => (
          <form onSubmit={handleSubmit}>
            <Box
              display="grid"
              gap="30px"
              gridTemplateColumns="repeat(4, minmax(0, 1fr))"
              sx={{
                "& > div": { gridColumn: isNonMobile ? undefined : "span 4" },
              }}
            >
              <FormGroup fullWidth>
                <h2>When to trigger reward</h2>
                <FormControlLabel
                  control={
                    <Checkbox
                      defaultChecked
                      style={{
                        color: "#00e676",
                      }}
                    />
                  }
                  label="Pull Request"
                />
                <FormControlLabel
                  control={<Checkbox style={{ color: "#00e676" }} />}
                  label="Issue Opened"
                />
                <FormControlLabel
                  control={<Checkbox style={{ color: "#00e676" }} />}
                  label="Issue Closed"
                />
                <FormControlLabel
                  control={<Checkbox style={{ color: "#00e676" }} />}
                  label="Push"
                />
              </FormGroup>
            </Box>
            <Box display="flex" justifyContent="center" mt="20px">
              <Button type="submit" color="secondary" variant="contained">
                Save
              </Button>
            </Box>
            <Box
              display="grid"
              gap="30px"
              gridTemplateColumns="repeat(4, minmax(0, 1fr))"
              sx={{
                "& > div": { gridColumn: isNonMobile ? undefined : "span 4" },
              }}
            >
              <FormGroup fullWidth>
                {/* <FormLabel component="p">When to trigger reward</FormLabel> */}
                <h2>How much to dispense</h2>
                <FormControl fullWidth>
                  <InputLabel id="demo-simple-select-label"># Items</InputLabel>
                  <Select
                    labelId="demo-simple-select-label"
                    id="demo-simple-select"

                    value={values.itemsToDispense}
                    label="Items To Dispense"
                    onChange={handleChange}
                    defaultValue={3}
                  >
                    <MenuItem value={1}>1</MenuItem>
                    <MenuItem value={3}>3</MenuItem>
                    <MenuItem value={5}>5</MenuItem>
                    <MenuItem value={10}>10</MenuItem>
                  </Select>
                </FormControl>
              </FormGroup>
            </Box>
            <Box display="flex" justifyContent="center" mt="20px">
              <Button type="submit" color="secondary" variant="contained">
                Save
              </Button>
            </Box>
            {/* <Box display="flex" justifyContent="end" mt="20px">
              <Button type="submit" color="secondary" variant="contained">
                Create New User
              </Button>
            </Box> */}
          </form>
        )}
      </Formik>
    </Box>
  );
};

const phoneRegExp =
  /^((\+[1-9]{1,4}[ -]?)|(\([0-9]{2,3}\)[ -]?)|([0-9]{2,4})[ -]?)*?[0-9]{3,4}[ -]?[0-9]{3,4}$/;

const checkoutSchema = yup.object().shape({
  firstName: yup.string().required("required"),
  lastName: yup.string().required("required"),
  email: yup.string().email("invalid email").required("required"),
  contact: yup
    .string()
    .matches(phoneRegExp, "Phone number is not valid")
    .required("required"),
  address1: yup.string().required("required"),
  address2: yup.string().required("required"),
});
const initialValues = {
  firstName: "",
  lastName: "",
  email: "",
  contact: "",
  address1: "",
  address2: "",
};

export default Form;
