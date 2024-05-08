#include <osg/Geode>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>


int main() {

    // Creamos el cubo utilizando ShapeDrawable y Box
    osg::ref_ptr<osg::ShapeDrawable> cubeDrawable = new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 1.0f));

    // Creamos un material para establecer el modo de color
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2f, 0.2f, 0.2f, 1.0f));
    material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f));

    // Aplicamos el material al conjunto de estado
    osg::ref_ptr<osg::StateSet> stateSetCube = cubeDrawable->getOrCreateStateSet();
    stateSetCube->setAttributeAndModes(material, osg::StateAttribute::ON);

    // Creamos un nodo Geode y le añadimos la forma del cubo
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(cubeDrawable);

    // Creamos un nodo MatrixTransform para rotar el cubo
    osg::ref_ptr<osg::MatrixTransform> cubeTransform = new osg::MatrixTransform;
    cubeTransform->addChild(geode);

    // Creamos un visor para visualizar la escena y configuramos el tamaño de la ventana
    osgViewer::Viewer viewer;
    viewer.setUpViewInWindow(200, 200, 1000, 800);

    // Usamos como escena el nodo MatrixTransform
    viewer.setSceneData(cubeTransform);

    // Establecemos el manipulador de cámara y ajustamos la distancia inicial
    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator();
    osg::Vec3d eye(0, 0, 5); // Ajustamos la posición inicial de la cámara
    osg::Vec3d center(0, 0, 0); // Ajustamos el punto hacia el que mira la cámara
    osg::Vec3d up(0, 1, 0); // Ajustamos el vector de dirección "arriba" de la cámara
    manipulator->setHomePosition(eye, center, up);
    viewer.setCameraManipulator(manipulator);

    // Configuramos la rotación del cubo
    float angle = 0.0f;
    while (!viewer.done()) {
        osg::Matrix rotationMatrix;

        // Rotación en el eje Y
        rotationMatrix.makeRotate(angle, osg::Vec3(0.0f, 1.0f, 0.0f));
        cubeTransform->setMatrix(rotationMatrix);

        angle += 0.01f;
        viewer.frame();
    }

    return 0;
}
